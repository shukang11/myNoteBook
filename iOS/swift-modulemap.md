
## 介绍

在 swift 环境中，有时候会有需要调用 C 的函数，这时候后一般的做法是 swift - OC - C 这样的过程，但是有没有更为优雅的方式呢？

现在我们可以通过 @import 来取代 以往的 #import & #include

相比以往的形式，新的形式具有如下好处

* 语义上完整描述了一个框架的作用
* 提高编译时可扩展性，只编译或 include 一次。避免头文件多次引用，只解析一次头文件甚至不需要解析（类似预编译头文件）
* 减少碎片化，每个 module 只处理一次，环境的变化不会导致不一致
* 对工具友好，工具（语言编译器）可以获取更多关于 module 的信息，比如链接库，比如语言是 C++ 还是 C
* 等等

## 使用

创建一个 module.map（或者 module.modulemap） 文件

![Image](/iOS/images/modulemap001.png)

modulemap 文件格式

```
module HC [system] {
    umbrella header "hc.h"
    export *
    
    explicit module Sub {
        header "sub.h"
        export *
    }
}


```

## 导入 Module Map 文件
创建好了 Module Map 文件之后，我们需要让编译器能够找到 Module Map 文件，这样才可以进行调用

我们进入 Build Settings 中，找到 Swift Compiler - Search Paths 部分下的 Import Paths，把 Module Map 文件的路径添加上


## 混编情况呢？

* 在创建Pod，且引入Objective-C语言开发的第三方公共库供Swift使用时，我们并不需要创建xxx-Bridge-Header.h桥文件去引入Objective-C的头文件， 这个工作是交由xxx-umbrella.h文件完成，这个文件的其中一个作用：其实和xxx-Bridge-Header.h桥文件的作用基本相同，向外界暴露Objective-C的头文件供Swift使用，实现Swift和Objective-C的混编。当你再次通过ss.source_files和ss.public_header_files暴露第三方公共的头文件时会重复定义，所以需要注释掉或删除掉ss.source_files和ss.public_header_files这两个参数及配置。

* 如果你的项目主要是采用Swift语言来写的，那么你就必须要创建xxx-Bridge-Heder.h桥文件来引入Objective-C的头文件，那有没有一种方式是可以不需要创建xxx-Bridge-Header.h桥文件的呢？

* 通过修改 podspec 文件， 使用 prepare_command 属性帮助我们自动创建 .modulemap 文件

> prepare_command属性的解释、使用场景及禁用条件：
> 
>prepare_command属性是下载Pod后将执行的bash脚本。此命令可用于创建、删除和修改下载的任何文件，并将在收集规范的其他文件属性的任何路径之前运行。
>
> 此命令在清理Pod和创建Pods项目之前执行。工作目录是Pod的根目录。
>
> prepare_command属性必须在主模块中使用。
> 
>如果pod安装了:path选项，则不会执行此命令。



****

## __链接__

* [Module System of Swift (简析 Swift 的模块系统)](http://andelf.github.io/blog/2014/06/19/modules-for-swift/)

* [Swift & C](https://imkcat.com/swift-and-c/)

*  [Swift/Objective-C-使用Cocoapods创建/管理私有库（高级用法）](https://wemp.app/posts/5d3eef42-d670-4e32-8751-05969a5cfa49)