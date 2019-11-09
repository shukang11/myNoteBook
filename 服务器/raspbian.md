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