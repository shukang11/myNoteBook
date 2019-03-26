# 

## Supervisor  [相关链接](https://www.restran.net/2015/10/04/supervisord-tutorial/)

安装 Python3 版本 

` pip3 install git+https://github.com/Supervisor/supervisor `

创建配置文件 

` echo_supervisord_conf > /etc/supervisord.conf `

or 

` sudo su - root -c "echo_supervisord_conf > /etc/supervisord.conf" `


为项目单独文件配置：

```

[program:myProgram]
directory=/home/pi/sky_tool/
command=pipenv run gunicorn -c gunicorn_config.py main:application
environment=SUPERSET_HOME=/home/qboxserver/.superset,SUPERSET_WEBSERVER_PORT=7070
autostart=true
autorestart=ture
stdout_logfile=/home/myname/test.log

```

rabbitmq-server