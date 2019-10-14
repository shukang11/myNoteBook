# docker 常用命令

* 安装Docker-compose
` sudo curl -L "https://github.com/docker/compose/releases/download/1.22.0/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose `

### 关于镜像（image）

 * `docker image ls` 查看本地镜像

 * `docker  image rm [镜像id]` 移除镜像

### 关于容器 （container）

* `docker container rm  [容器]` 如果要删除一个运行中的容器， 可以添加 -f 参数。Docker 会发送 SIGKILL 信号给容器。


### 关于构建 （build）

* `docker build -t name .` 

[构建一个镜像](https://www.runoob.com/docker/docker-build-command.html)

* `docker tag sky_tool account/tagName:version` 打标签

* `docker push account/tagName:latest` 推送到仓库

### 关于运行 （run）

[Docker的持久化存储和数据共享](https://juejin.im/post/5b6d4439f265da0f800e0d5a)
[Docker with Mysql官方文档](https://yeasy.gitbooks.io/docker_practice/appendix/repo/mysql.html)

* `docker pull account/tagName:version ` 从仓库拉取项目

* `docker pull [tag]` 从仓库中拉取镜像

* `docker run [tag] [-d 后台运行] [-p 内部端口映射到主机上] [command]` 运行一个容器

* `docker run -t -i image /bin/bash` 运行容器

```
参数解读
--name 镜像名称
-p 3307:3306 在容器中使用3306端口，映射到本机的3307端口
-d 使用守护进程运行，服务挂在后台
-v /path/to/local 将主机的目录作为容器的数据卷
```

### 其他

* `docker stats` 查看状态

* `docker login` 登录，使用 docker id 而不是 邮箱


