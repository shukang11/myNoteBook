# 使用 swift package 开发命令行工具

https://www.jianshu.com/p/1c008bb2656f

`版本要求： xcode 8`

## 初始化命令 `swift package init`

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