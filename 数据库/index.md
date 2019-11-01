## 相关软件备忘

* glances 系统检测

[Unit]
Description = Glances in Web Server Mode
After = network.target
[Service]
ExecStart = /root/.pyenv/shims/glances  -w  -t  5  # glances路径因安装方法不同根据实际情况确定，可使用 which glances 命令获取
[Install]
WantedBy = multi-user.target