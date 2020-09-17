
## Cocoapods

### 使用Pod创建私有库过程

* __创建 pod 描述模板__

` pod spec create <pod_name> `


** __使用模板创建库__

` pod lib create <pod_name> `

* __验证项目是否可以正常编译__

` pod lib lint [--allow-warnings] `


## Carthage

1. 安装

可是使用 `brew` 来安装: `brew install Carthage `

2. 使用

进入到项目目录， ` touch Cartfile ` 创建文件

可以通过 `github  "AFNetworking/AFNetworking" ` 来安装，或者通过 `git "https://github.com/AFNetworking/AFNetworking.git" `来安装

3. 安装

` Carthage update --platform iOS ` 只针对 iOS 平台编译

`--no-use-binaries` 选项可以设置不使用远端的二进制，而是在本地生成二进制

> 如果失败的话，先用Xcode打开你的项目，Product > Scheme > Manage Schemes 在新窗口中，勾选上 Shared，点击 Close。在终端再次执行这个命令

4. 配置项目

打开项目，点击 `Target -> Build Phases -> Link Library with Libraries` 选择 `Carthage/Build` 目录中要导入的 `framework`

5. 添加编译脚本

点击 `Build Phases` ，点击 `“+” -> New Run Script Phase`

添加添加脚本 `/usr/local/bin/Carthage copy-frameworks`

添加"Input Files" `$(SRCROOT)/Carthage/Build/iOS/AFNetworking.framework`


## Cocoapods与Flutter


### links
* [Carthage安装和使用教程](https://juejin.im/post/5bfc408e6fb9a049f745e1b9)
* [Carthage 让项目支持及使用，第三方静态库转为动态库](https://www.cnblogs.com/jys509/p/10334527.html)
* [Carthage 官文翻译](https://www.jianshu.com/p/e0c0ceee8ab2)