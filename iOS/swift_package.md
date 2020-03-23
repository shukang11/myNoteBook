# 使用 swift package 开发命令行工具

https://www.jianshu.com/p/1c008bb2656f

`版本要求： xcode 8`

## 初始化命令 `swift package init --type executable`

使用  `--type executable` 选项表示是命令行的项目

会在当前文件夹下创建相关的文件


## 生成 xcodeproj

 `swift package generate-xcodeproj`

## 编译 

`swift build`


## 引用第三方库

在 Package.swift 文件中编辑

```
 dependencies: [
        // Dependencies declare other packages that this package depends on.
        // .package(url: /* package url */, from: "1.0.0"),
    ],

```

之后需要编译一下， 重新执行 `swift package generate-xcodeproj`

## 使用ArgumentParser

这是苹果官方的命令行参数解析库

使用了属性装饰器

``` swift
struct Heic: ParsableCommand {
    
    @Option(name: [.customShort("i"), .customLong("input", withSingleDash: false)], help: "Input foloder of images")
    var inputFolder: String?
    
    @Option(name: [.customShort("o"), .customLong("output", withSingleDash: false)], help: "Out put file of images")
    var outputFile: String?
    
    @Option(name: [.customShort("q"), .customLong("quality", withSingleDash: false)], help: "quality of image")
    var quality: Float?
    
    func run() throws {
        let output = outputFile ?? "output.heic"

        let input = inputFolder ?? "./input"
        let q = quality ?? 0.9
        
        let source = URL(fileURLWithPath: input, isDirectory: true)
        let out = URL(fileURLWithPath: output, isDirectory: false)
        var sourceImageUrls = [URL]()
        for index in 1...16 {
            let filename = String(format: "%02d", index)
            sourceImageUrls.append(source.appendingPathComponent("\(filename).png"))
        }
        
        if #available(OSX 10.13, *) {
//            conver()
            convert(images: sourceImageUrls, heicUrl: out, quality: q)
        } else {
            // Fallback on earlier versions
        }
    }
}

Heic.main()


```