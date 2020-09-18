# Shell 常用命令

#### grep 命令(global search regular expression)

> 它能使用正则表达式搜索文本，并把匹配的行打印出来

参数

* `-E` 将样式为延伸的正则表达式来使用
* `-i` 忽略大小写的差别


### 获得命令输出到变量

``` shell
将 `git status` 的结果赋予 statusInfo 变量
statusInfo=`git status`
```

### 执行方法

```
function foo() {
    # 获得第一个函数
    echo $1
}

# 执行
foo "im param1"
```