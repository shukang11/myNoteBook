# docker 常用命令

* 安装Docker-compose
` sudo curl -L "https://github.com/docker/compose/releases/download/1.22.0/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose `

### 关于镜像（image）

 * `docker image ls` 查看本地镜像

 * `docker  image rm [image]` 移除镜像

 * `docker inspect [image]` 查看镜像信息

### 关于容器 （container）

* `docker container rm  [容器]` 如果要删除一个运行中的容器， 可以添加 -f 参数。Docker 会发送 SIGKILL 信号给容器。

* `docker ps [-l -a]` 查看容器 其中 -a 是列出所有容器， -l 是列出最近的一个容器

* `docker inspect [id]` 查看具体的容器信息

* `docker rm [id]`  删除一个容器，正在运行的容器不可删除

* `docker top` 查看运行中容器内进程的情况

* `docker attach [id]` 连接到一个运行中的容器

* `docker exec [id] [command]` 在容器中启动新的进程


### 关于构建 （build）

* `docker build -t name .` 

[构建一个镜像](https://www.runoob.com/docker/docker-build-command.html)

* `docker tag sky_tool account/tagName:version` 打标签

* `docker push account/tagName:latest` 推送到仓库

* `docker commit `

### [关于Dockerfile](#Dockerfile)

### 关于运行 （run）

[Docker的持久化存储和数据共享](https://juejin.im/post/5b6d4439f265da0f800e0d5a)
[Docker with Mysql官方文档](https://yeasy.gitbooks.io/docker_practice/appendix/repo/mysql.html)

* `docker pull account/tagName:version ` 从仓库拉取项目

* `docker pull [tag]` 从仓库中拉取镜像

* `docker run [tag] [-d 后台运行] [-p 内部端口映射到主机上] [command]` 运行一个容器

* `docker run -t -i image /bin/bash` 运行容器

* `docker exec -it container /bin/bash` 进入一个已经存在的容器

* `docker start [-i] [containerId]` 重新运行一个容器

```
参数解读
--name 镜像名称
-p 3307:3306 在容器中使用3306端口，映射到本机的3307端口
-d 使用守护进程运行，服务挂在后台
-it 交互式运行 如果想退出交互式容器 `ctrl + p ctrl + q`，此时容器在后台运行 想重新进入交互式环境 `docker attach [id]`
-v /path/to/local 将主机的目录作为容器的数据卷
```

### 基本操作


### 数据卷(Volume)


### 其他

* `docker stats` 查看状态

* `docker login` 登录，使用 docker id 而不是 邮箱

ref: [链接](https://www.jianshu.com/p/9f13d02028c5)
```
# 关闭所有的容器
docker stop $(docker ps -a -q)
# 删除所有的容器
docker rm $(docker ps -a -q)
# 启动Mysql容器 -d(后台启动) -p 配置端口 -v 配置映射把服务器的文件映射到容器内（对于mysql来说使用相对路径把容器内的sql数据映射到服务器上）
# --name 取得别名  zhaozn91/mysql:latest 镜像名称 
docker run -d -p 3306:3306 -v docker_mysql:/var/lib/mysql --name=my_mysql zhaozn91/mysql:latest
# redis我没有配置把数据映射到本地路径，需要的可以按照mysql自己配置
docker run -d -p 6379:6379 --name=my_redis zhaozn91/redis:ubuntu
# python容器多出来一个 --link=--link=my_mysql:db 相当于把两个容器关联可以使python容器访问mysql容器，my_mysql就是自己命名的别名 db就是在python容器中自己为my_mysql取得别名， 在Python程序中把连接数据库host=db就可以了，redis相同操作
docker run -d -v /home/docker/init_python.sh:/home/start.sh -v /home/XViews2:/home/XViews2 --name=my_python --link=my_redis:redis --link=my_mysql:db zhaozn91/python3.5:ubuntu
# nginx容器
docker run -d -p 80:80 -v /home/xview/:/home/xview/ --name=my_nginx --link my_python:my_python zhaozn91/nginx:ubuntu


```


### Dockerfile

示例1：
起一个nginx服务，并将本地一个目录映射到docker中
``` shell
docker container run \
  -d \
  -p 127.0.0.2:8080:80 \
  --rm \
  --name mynginx \
  --volume "$PWD/html":/usr/share/nginx/html \
  nginx

```

### Docker数据卷

> 是经过特殊设计的目录，可以绕过联合文件系统，为一个或者多个容器提供访问。

> 数据卷的设计目的是在于数据的永久化，完全独立于容器的声明周期

 * 为容器添加数据卷: ` sudo docker run -v ~/container_data:/data -it ubuntu /bin/bash `

 如果本地并不存在 `~/container_data` 目录，则会创建目录

 还可以通过在 `Dockerfile` 中，添加 VOLUMN ['path'] 来添加卷，但是通过这种方式添加的卷，并不能在多个容器中共享数据, 想要实现挂载宿主机目录，需要通过挂载数据卷容器来实现

 ### Docker数据卷容器

 通过创建一个容器，指定了挂载目录，其他容器使用 `--volumes-from` 来连接到这个容器，使用挂载的目录

 ### Docker数据卷的备份和还原 
 
 ` docker run --volumes-from [contianer name] -v ${PWD}:/backup ubuntu tar cvf /backup/backup.tar [container data volume]`


 ### 示例 部署一个 flask + mysql + redis 的应用

1. 需要的容器: `python mysql redis`

2. 把 redis 服务跑起来

` docker run --name redis_6379 -d -p 6379:6379 redis --appendonly yes `

3. 把 mysql 服务跑起来

` docker run --name mysql_3306 -p 127.0.0.1:3306:3306 -e MYSQL_ROOT_PASSWORD=12345678 -e MYSQL_DATABASE=sky_main -d mysql --character-set-server=utf8mb4 --collation-server=utf8mb4_unicode_ci `

> MYSQL_DATABASE 创建数据库实例

