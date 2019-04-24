
## Supervisor  [相关链接](https://www.restran.net/2015/10/04/supervisord-tutorial/)

安装 Python3 版本 

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