# [Guide](https://www.appcoda.com.tw/xcconfig-guide/)

##  介绍

在开发过程中，会在多个配置之间切换，如果使用硬编码，工作量变大的同时也会不好维护。

想要使用多种配置的切换，可以参考如下方法：

* ## 多 Target

![Image](/iOS/images/Duplicate-target.png)

这样可以指定不同的 ImageAsset、BundleID、info.plist，也可以指定`Preprocessor Macros`

针对 Swift 项目，预编译值不再被支持，我们将设置 `Swift Complier - Custom Flags` 设置 `-DEVELOPMENT`来使用相对应设置

```
#if DEVELOPMENT
let SERVER_URL = "http://dev.server.com/api/"
let API_TOKEN = "DI2023409jf90ew"
#else
let SERVER_URL = "http://prod.server.com/api/"
let API_TOKEN = "71a629j0f090232"
#endif

```

* ## Xcode Configuration

设置 

![Image](/iOS/images/Xcode-Configuration-setting.png)

分别设置每个配置文件

Debug.xcconfig:
```
IS_APP_NAME = Donate Debug
IS_APP_VERSION = 0.3
IS_APP_BUNDLE_ID = com.intensifystudio.DonateDebug
```

Staging.xcconfig:
```
IS_APP_NAME = Donate Staging
IS_APP_VERSION = 0.2
IS_APP_BUNDLE_ID = com.intensifystudio.DonateStaging
```

Release.xcconfig:
```
IS_APP_NAME = Donate
IS_APP_VERSION = 0.1
IS_APP_BUNDLE_ID = com.intensifystudio.DonateRelease
```

![Image](/iOS/images/Xcode-config-set.png)