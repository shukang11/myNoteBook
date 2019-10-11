在使用 AVAudioRecorder 的时候，如果录音呗中断了，会导致整个录音中断，即使是继续录音也只是创建了另外一个录音文件。 在此前提下，开始了解更底层的音频框架

# AudioEngine

* ### AVAudioEngine API的基本概念是建立一个音频的节点图，从源节点 (播放器和麦克风) 以及过处理 (overprocessing) 节点 (混音器和效果器) 到目标节点 (硬件输出)。每一个节点都具有一定数量的输入和输出总线，同时这些总线也有良好定义的数据格式。这种结构使得它非常的灵活和强大。而且它集成了音频单元 (audio unit)。

* __AVAudioEngine__

>  负责管理所有的音频节点
>
> 连接所有的节点，使其构成一条链

```
 // 1. Create engine (example only, needs to be strong   reference)
     AVAudioEngine *engine = [[AVAudioEngine alloc] init];
     // 2. Create a player node
     AVAudioPlayerNode *player = [[AVAudioPlayerNode alloc] init];
     // 3. Attach node to the engine
     [engine attachNode:player];
     // 4. Connect player node to engine's main mixer
     AVAudioMixerNode *mixer = engine.mainMixerNode;
     [engine connect:player to:mixer format:[mixer outputFormatForBus:0]];

```

* __AVAudioNode__

> AVAudioInputNode
>
> AVAudioOutputNode
>
> AVAudioMixerNode

* __AVAudioFile__

> 读写所有Core Audio支持的音频格式
>
> 读写自动编码解码
>

```
// Read
NSURL *url = [[NSBundle mainBundle] URLForAuxiliaryExecutable:@"Your.mp3"];
     // Create AVAudioFile
     AVAudioFile *file = [[AVAudioFile alloc] initForReading:url error:nil];
     // Create AVAudioPCMBuffer
     AVAudioFormat *format = file.processingFormat;
     AVAudioFrameCount capacity = (AVAudioFrameCount)file.length;
     AVAudioPCMBuffer *buffer = [[AVAudioPCMBuffer alloc] initWithPCMFormat:format frameCapacity:capacity];
     // Read AVAudioFile -> AVAudioPCMBuffer
     [file readIntoBuffer:buffer error:nil];


// Write
let audioFile = try! AVAudioFile(forWriting: recordingPath, settings: [AVFormatIDKey: kAudioFormatMPEG4AAC], commonFormat: .pcmFormatFloat32, interleaved: isInterleaved)
```
* __AVAudioFormat__

* __AVAudioPCMBuffer__

* __AVAudioPlayerNode__

```
//Immediate File Playback
     [playerNode scheduleFile:audioFile atTime:nil completionHandler:nil];
     [playerNode play];

     //Future Buffer Playback
     [playerNode scheduleBuffer:audioBuffer completionHandler:nil];
     [playerNode play];

     // Play audio file 5 seconds from now
     double sampleRate = buffer.format.sampleRate;
     double sampleTime = sampleRate * 5.0;
     AVAudioTime *futureTime = [AVAudioTime timeWithSampleTime:sampleTime atRate:sampleRate];

     [playerNode scheduleBuffer:audioBuffer atTime:futureTime options:0 completionHandler:nil];
     [playerNode play];

```

```
audioEngine = AVAudioEngine()
        audioPlayerNode = AVAudioPlayerNode()
        audioMixerNode = audioEngine.mainMixerNode

        let frameLength = UInt32(256)
        audioBuffer = AVAudioPCMBuffer(PCMFormat: audioPlayerNode.outputFormatForBus(0), frameCapacity: frameLength)
        audioBuffer.frameLength = frameLength

        audioInputNode = audioEngine.inputNode

        audioInputNode.installTapOnBus(0, bufferSize:frameLength, format: audioInputNode.outputFormatForBus(0), block: {(buffer, time) in
            let channels = UnsafeArray(start: buffer.floatChannelData, length: Int(buffer.format.channelCount))
            let floats = UnsafeArray(start: channels[0], length: Int(buffer.frameLength))

            for var i = 0; i < Int(self.audioBuffer.frameLength); i+=Int(self.audioMixerNode.outputFormatForBus(0).channelCount)
            {
                // doing my real time stuff
                self.audioBuffer.floatChannelData.memory[i] = floats[i];
            }
            })

        // setup audio engine
        audioEngine.attachNode(audioPlayerNode)
        audioEngine.connect(audioPlayerNode, to: audioMixerNode, format: audioPlayerNode.outputFormatForBus(0))
        audioEngine.startAndReturnError(nil)

        // play player and buffer
        audioPlayerNode.play()
        audioPlayerNode.scheduleBuffer(audioBuffer, atTime: nil, options: .Loops, completionHandler: nil)
        
```

## AudioQueue in C [链接](https://github.com/brownfeng/AudioQueueServiceDemo/blob/master/Recorder/Recorder.m)
```
#import <Foundation/Foundation.h>
#import <AudioToolbox/AudioToolbox.h>

static const int kNumberBuffers = 3;
typedef struct AQRecorderState {
    AudioStreamBasicDescription  mDataFormat;
    AudioQueueRef                mQueue;
    AudioQueueBufferRef          mBuffers[kNumberBuffers];
    AudioFileID                  mAudioFile;
    UInt32                       bufferByteSize;
    SInt64                       mCurrentPacket;
    bool                         mIsRunning;
} AQRecorderState;


static void HandleInputBuffer (void                                *aqData,
                               AudioQueueRef                       inAQ,
                               AudioQueueBufferRef                 inBuffer,
                               const AudioTimeStamp                *inStartTime,
                               UInt32                              inNumPackets,
                               const AudioStreamPacketDescription  *inPacketDesc
){
    AQRecorderState *pAqData = (AQRecorderState *) aqData;
    if(inNumPackets == 0 && pAqData->mDataFormat.mBytesPerPacket!=0) {
        inNumPackets = inBuffer->mAudioDataByteSize / pAqData->mDataFormat.mBytesPerPacket;
    }
    
    if (AudioFileWritePackets (pAqData->mAudioFile,false,inBuffer->mAudioDataByteSize,inPacketDesc,pAqData->mCurrentPacket,&inNumPackets, inBuffer->mAudioData) == noErr) {
        pAqData->mCurrentPacket += inNumPackets;
    }
    if (pAqData->mIsRunning == 0)
        return;
    
    AudioQueueEnqueueBuffer(pAqData->mQueue,inBuffer,0,NULL);
}


void DeriveBufferSize (AudioQueueRef audioQueue,AudioStreamBasicDescription *ASBDescription, Float64 seconds,UInt32                       *outBufferSize) {
    static const int maxBufferSize = 0x50000;
 
    int maxPacketSize = (*ASBDescription).mBytesPerPacket;
    if (maxPacketSize == 0) {
        UInt32 maxVBRPacketSize = sizeof(maxPacketSize);
        AudioQueueGetProperty(audioQueue,kAudioQueueProperty_MaximumOutputPacketSize,&maxPacketSize,&maxVBRPacketSize);
    }
    
    Float64 numBytesForTime =
    (*ASBDescription).mSampleRate * maxPacketSize * seconds;
    *outBufferSize = numBytesForTime < maxBufferSize ? numBytesForTime : maxBufferSize;
}

OSStatus SetMagicCookieForFile(AudioQueueRef inQueue, AudioFileID  inFile) {
    OSStatus result = noErr;
    UInt32 cookieSize;
    if (AudioQueueGetPropertySize (inQueue,kAudioQueueProperty_MagicCookie,&cookieSize) == noErr) {
        char* magicCookie = (char *) malloc (cookieSize);
        if (AudioQueueGetProperty (inQueue,kAudioQueueProperty_MagicCookie,magicCookie,&cookieSize) == noErr){
            result = AudioFileSetProperty (inFile,kAudioFilePropertyMagicCookieData,cookieSize,magicCookie);
        }

        free (magicCookie);
    }
    return result;
}


int main(int argc, const char * argv[]) {
    @autoreleasepool {
        AQRecorderState aqData = {0};
        //设置formatter
        aqData.mDataFormat.mFormatID         = kAudioFormatLinearPCM;
        aqData.mDataFormat.mSampleRate       = 44100.0;
        aqData.mDataFormat.mChannelsPerFrame = 2;
        aqData.mDataFormat.mBitsPerChannel   = 16;
        aqData.mDataFormat.mBytesPerPacket   = aqData.mDataFormat.mBytesPerFrame =  aqData.mDataFormat.mChannelsPerFrame * sizeof (SInt16);
        aqData.mDataFormat.mFramesPerPacket  = 1;
        AudioFileTypeID fileType= kAudioFileAIFFType;
        aqData.mDataFormat.mFormatFlags = kLinearPCMFormatFlagIsBigEndian | kLinearPCMFormatFlagIsSignedInteger | kLinearPCMFormatFlagIsPacked;
        
        AudioQueueNewInput (&aqData.mDataFormat,HandleInputBuffer,&aqData,NULL,kCFRunLoopCommonModes,0,&aqData.mQueue);
        
        UInt32 dataFormatSize = sizeof (aqData.mDataFormat);
        AudioQueueGetProperty (aqData.mQueue,kAudioQueueProperty_StreamDescription,&aqData.mDataFormat,&dataFormatSize);
        
        CFURLRef audioFileURL = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, CFSTR("output.caf"), kCFURLPOSIXPathStyle, false);
        
        AudioFileCreateWithURL(audioFileURL,fileType, &aqData.mDataFormat, kAudioFileFlags_EraseFile, &aqData.mAudioFile);
        
        DeriveBufferSize(aqData.mQueue, &aqData.mDataFormat, 0.5,  &aqData.bufferByteSize);
        
        for (int i = 0; i < kNumberBuffers; ++i) {
            AudioQueueAllocateBuffer(aqData.mQueue,aqData.bufferByteSize,&aqData.mBuffers[i]);
            AudioQueueEnqueueBuffer (aqData.mQueue,aqData.mBuffers[i], 0, NULL);
        }
        
        aqData.mCurrentPacket = 0;
        aqData.mIsRunning = true;
        AudioQueueStart (aqData.mQueue,NULL);
        
        printf("Recording, press <return> to stop:\n");
        getchar();
        printf("* recording done *\n");
        
        AudioQueueStop ( aqData.mQueue,true);
        aqData.mIsRunning = false;
        AudioQueueDispose (aqData.mQueue, true );
        AudioFileClose (aqData.mAudioFile);
    }
    return 0;
}

```

## Reference

* [ios利用mic采集Pcm转为AAC，AudioQueue、AudioUnit(流式)](https://juejin.im/post/5a8fdd915188255de20105ef)

* [关于实现唱吧清唱功能的理解](https://oliverqueen.cn/2018/06/19/MusicAbout/)