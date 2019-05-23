
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

## __链接__

* [Module System of Swift (简析 Swift 的模块系统)](http://andelf.github.io/blog/2014/06/19/modules-for-swift/)