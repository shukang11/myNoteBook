# docker 常用命令

### 关于镜像（image）

 * `docker image ls` 查看本地镜像

 * `docker  image rm [镜像id]` 移除镜像

### 关于容器 （container）

* `docker container rm  [容器]` 如果要删除一个运行中的容器， 可以添加 -f 参数。Docker 会发送 SIGKILL 信号给容器。


### 关于构建 （build）

* `docker build -t name .` 构建一个镜像

### 关于运行 （run）

