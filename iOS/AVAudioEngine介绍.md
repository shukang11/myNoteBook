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
NSURL *url = [[NSBundle mainBundle] URLForAuxiliaryExecutable:@"Your.mp3"];
     // Create AVAudioFile
     AVAudioFile *file = [[AVAudioFile alloc] initForReading:url error:nil];
     // Create AVAudioPCMBuffer
     AVAudioFormat *format = file.processingFormat;
     AVAudioFrameCount capacity = (AVAudioFrameCount)file.length;
     AVAudioPCMBuffer *buffer = [[AVAudioPCMBuffer alloc] initWithPCMFormat:format frameCapacity:capacity];
     // Read AVAudioFile -> AVAudioPCMBuffer
     [file readIntoBuffer:buffer error:nil];

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