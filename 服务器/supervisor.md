
# Supervisor  [相关链接](https://www.restran.net/2015/10/04/supervisord-tutorial/)

* [进程是如何工作的](#进程是如何工作的)
* [安装](#安装)
* [配置文件](#创建配置文件)

## 进程是如何工作的
> 在 unix 上启动进程只有两种，但是对于开发者来说，只有一种

* 第一种是通过 Init 来启动，当 Unix 计算机启动，内核加载初始化后，内核只启动一个进程，就是 Init，这个进程是计算机最先启动的，之后由 Init 来加载其余进程

* 第二种则是通过系统命令 `fork()` ，这个命令会复制一个进程然后运行，复制的进程为 __子进程__，被复制的进程为 __父进程__，`fork()`命令返回 0 给 __子进程__， 返回 __子进程__ 的`PID`给 __父进程__ ；

> 但是第二种方法只是复制了一模一样的进程，对我们来说意义不大，于是可以在 `fork()` 之后， 通过 `exec()` 命令，来开启新的进程，这条命令会将当前进程替换为新的进程，通过这两个命令，我们可以完成开启新进程的工作，甚至使用 `wait()` 命令来监视子进程



## 安装 

> Python3 版本 

` pip3 install git+https://github.com/Supervisor/supervisor `

* 创建配置文件 

` echo_supervisord_conf > /etc/supervisord.conf `

或者 

` sudo su - root -c "echo_supervisord_conf > /etc/supervisord.conf" `


为项目单独文件配置：

```

[program:myProgram]
directory=/home/pi/sky_tool/; 执行命令前会切换到此目录
command=pipenv run gunicorn -c gunicorn_config.py main:application ; 执行的命令
environment=SUPERSET_HOME=/home/qboxserver/.superset,SUPERSET_WEBSERVER_PORT=7070 ; 可设置环境变量
autostart=true
autorestart=ture ;错误时尝试重新启动
stdout_logfile=/home/myname/test.log

```

rabbitmq-server