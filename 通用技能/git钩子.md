# git hooks

> Git hooks 允许在git下，几个关键操作可以自定义自己的操作，目前一些常用的场景如下：

- 在使用 `git commit` 命令可以检查提交内容是否符合规范，如果不规范则不允许提交

- 在 ` git push ` 的同时也调用远程服务器，执行某些操作，例如：部署，打包，备份等等

- ...

在这个场景中，将了解一些我不是很常用的git 命令，同时使用python来运行

### 钩子函数在哪里？

- 在git的分支下，所有的钩子函数都存在于 `.git/hooks/` 目录下，如果没有此目录可以创建，改目录中一般会有一些 `.sample` 后缀的文件，这些是一些预置的文件，如果想要某一个钩子生效，只需要把后缀去掉即可。

- 由于我对shell不是很熟练，所以将使用 `python`与`shell` 脚本执行。

### 第一个例子

> 将启用 `pre-commit` 脚本，来检查提交格式是否符合规则

这里我们使用了 `git symbolic-ref` 命令（[文档](https://cloud.tencent.com/developer/section/1138783)）
作用是，获得当前分支的名称，来对比是否是开发分支，在这里，如果返回一个非0值表示失败，将会终止提交

``` python
#!/usr/bin/env python

import sys, os
from subprocess import check_output

# 检测我们所在的分支
branch = check_output(['git', 'symbolic-ref', '--short', 'HEAD']).strip()
bran = str(branch)
if bran == 'master':
	print('请不要在{bran}分支提交'.format(bran=bran))
	sys.exit(1)
print('你正在{bran}分支提交'.format(bran=bran))

```

### 第二个例子

我们将通过github仓库，在本地推送到远程的时候同步更新服务器的内容,这些需要分别在本地和服务器修改

##### 1 登录远程服务器，选择一个目录，使用 `git init --bare` 命令创建一个裸仓库

``` 
git init --bare xxx-bare.git
# 或者
mkdir xxx-bare.git
cd xxx-bare.git
git init --bare

```

##### 2 配置git hook
将目录切换到 hooks，我们将调用 `cp post-update.sample post-update` 使钩子生效，并修改
```
unset GIT_DIR 
DIR_ONE=/home/user/www/blog／  #此目录为服务器页面展示目录 
cd $DIR_ONE

git init
git remote add origin ~/repos/xxx-bare.git
git clean -df
git pull origin master

```

##### 3 在本地添加服务器
```
git remote add origin user@1.2.3.4:/home/USER/repos/xxx-bare.git  #添加远程仓库源
//例如git remote add origin ssh://root@41.72.11.11:26244/home/USER/repos/xxx-bare.git  #远程仓库带端口写法
git push origin master
```
你也可以设置其他的名称，这些并不冲突。

### 文档资料链接
- [官方文档](https://www.git-scm.com/book/zh/v2/%E8%87%AA%E5%AE%9A%E4%B9%89-Git-Git-%E9%92%A9%E5%AD%90)

- [用 Git 钩子进行简单自动部署](https://aotu.io/notes/2017/04/10/githooks/index.html)

- [Git 钩子 hook 介绍与使用](https://www.jianshu.com/p/f3d17c11bb8a)
