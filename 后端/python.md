#python 笔记

##  pyenv 离线安装

` cd ~/.pyenv/ && mkdir cache/`

下载安装包 `wget https://www.python.org/ftp/python/3.5.4/Python-3.5.4.tar.xz `

安装 ` pyenv install 3.5.4 `

# 

## Supervisor  [相关链接](https://www.restran.net/2015/10/04/supervisord-tutorial/)

安装 Python3 版本 ` pip3 install git+https://github.com/Supervisor/supervisor `

创建配置文件 

` echo_supervisord_conf > /etc/supervisord.conf `

or 

` sudo su - root -c "echo_supervisord_conf > /etc/supervisord.conf" `


为项目单独文件配置：

```

[program:myProgram]
directory=/home/pi/sky_tool/
command=pipenv run gunicorn -c gunicorn_config.py main:app
autostart=true
autorestart=ture
stdout_logfile=/home/myname/test.log

```

### 常用命令

## jupyter

安装好之后 

启动 `jupyter notebook` 启动