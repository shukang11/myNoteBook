# 目录

* [docker](/服务器/docker.md)

* [nginx](/服务器/nginx.md)

*[oauth](/服务器/oauth.md)

* [respbian](/服务器/raspbian.md)

* [supervisor](/服务器/supervisor.md)


## 软件备忘

* glances 系统检测

[Unit]
Description = Glances in Web Server Mode
After = network.target
[Service]
ExecStart = /root/.pyenv/shims/glances  -w  -t  5  # glances路径因安装方法不同根据实际情况确定，可使用 which glances 命令获取
[Install]
WantedBy = multi-user.target