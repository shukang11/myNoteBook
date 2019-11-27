#python 笔记

# setup 构建包

#### setup函数各参数详解

```
  --name              包名称
  --version (-V)      包版本
  --author            程序的作者
  --author_email      程序的作者的邮箱地址
  --maintainer        维护者
  --maintainer_email  维护者的邮箱地址
  --url               程序的官网地址
  --license           程序的授权信息
  --description       程序的简单描述
  --long_description  程序的详细描述
  --platforms         程序适用的软件平台列表
  --classifiers       程序的所属分类列表
  --keywords          程序的关键字列表
  --packages  需要打包的目录列表
  --py_modules  需要打包的python文件列表
  --download_url  程序的下载地址
  --cmdclass  
  --data_files  打包时需要打包的数据文件，如图片，配置文件等
  --scripts  安装时需要执行的脚步列表

```

* 安装包 `python setup.py install`

* 开发模式安装包 `python setup.py develop`

- 之后就可以通过 ` python <package_name> <command> ` 来调用

* 卸载包 `python setup.py uninstall`

#### setup.py打包命令各参数详解

```
  --python setup.py build     # 仅编译不安装
  --python setup.py install    #安装到python安装目录的lib下
  --python setup.py sdist      #生成压缩包(zip/tar.gz)
  --python setup.py bdist_wininst  #生成NT平台安装包(.exe)
  --python setup.py bdist_rpm #生成rpm包

```