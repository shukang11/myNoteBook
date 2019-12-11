# raspbian

#### 写入系统

### 1. sd卡插入读卡器并查看磁盘序号

`diskutil list`

### 2.移除挂载的盘 

`diskutil unmountDisk <disk>`

### 3.写入镜像

`sudo dd bs=1m if=xxxxx.img of=/dev/rdiskn conv=sync`

### 安装 pyenv 

1. 安装依赖

` sudo apt-get install -y make build-essential libssl-dev zlib1g-dev libbz2-dev libreadline-dev libsqlite3-dev wget curl llvm `

2. 安装 

`$ curl -L https://raw.githubusercontent.com/pyenv/pyenv-installer/master/bin/pyenv-installer | bash`


### 安装 zsh

```
apt install zsh

sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"

```

### 安装 golang

` sudo apt install golang `

### 安装 node

建议直接从 nvm 官网拉取代码构建

### [配置dlna](http://shumeipai.nxez.com/2015/07/12/raspberry-pi-install-dlna-streaming-media-server.html)
### [SAMBA](https://blog.csdn.net/u013181595/article/details/77150802)

### frp

服务端配置

```
[common]
bind_port = 5000 ; 绑定的端口，需要与客户端中 server_port 参数保持一致
privilege_token = privilege_token_value ; 自定义值，必须与客户端中的 privilege_token 保持一致
vhost_http_port = 80 ; 虚拟主机运行在本机的端口，如果 vps 有服务占用了端口，应当更换
dashboard_port = dashboard_port_number ; frp 后台服务页面的端口，如果设置 8000，便可通过 http://yourip:8000 来访问 frps 的后台页面
dashboard_user = dashboard_user_name ; frp 后台服务页面的管理员用户名
dashboard_pwd = dashboard_pwd_value ; frp 后台服务页面的管理员密码

```

* 运行代码 `./frps -c ./frps.ini`

```
[common]
server_addr = your_server_ip ; 服务器端的 ip
server_port = 5000 ; 服务器端的端口，即 bind_port
privilege_token = privilege_token_value ; 同服务器端的 privilege_token 保持一致
login_fail_exit = false ; 失败时自动重连
remote_port = 5010 ; 远程端口，即 ssh 连接树莓派时的端口
​
[ssh]
type = tcp
local_ip = 127.0.0.1
local_port = 22

[web]
type = http
local_port = 5010
custom_domains = <remote_ip>

```
* 运行代码 ` ./frps -c ./frps.ini `

* 连接 ` ssh -oPort=<remote_port> pi@<your_server_ip> `