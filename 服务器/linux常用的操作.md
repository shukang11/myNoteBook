# 索引

* [挂载硬盘](#挂载硬盘)

* [无屏幕配置树莓派wifi连接](#无屏幕配置树莓派wifi连接)

* [vim常用命令](#vim常用命令)

* ## 切换界面与命令行

` startx `

* ## 查看磁盘空间
 
 `df -h`

## 挂载硬盘
 * 查看挂载的硬盘

` sudo fdisk -l`

* 创建一个目录

`sudo mkdir /home/pi/disk`

* 挂载命令

`sudo mount /dev/sda3 /home/pi/disk`

* 卸载命令

`sudo umount /home/pi/disk`

* 安装NTFS格式可读写软件

`sudo aptitude install ntfs-3g`

* 安装exFAT格式的读写

`sudo apt-get install exfat-fuse`

* 加载内核模块

`modprobe fuse`

* 让移动硬盘开机自动挂载

`sudo vim /etc/fstab`

最后添加一行

`/dev/sda3  /home/pi/toshiba ntfs-3g defaults,noexec,umask=0000 0 0`

如果挂载出错

`sudo fuser -m -u /dev/sda3 && sudo kill 1308`

## 无屏幕配置树莓派wifi连接
> 将刷好 Raspbian 系统的 SD 卡用电脑读取。在 boot 分区，也就是树莓派的 /boot 目录下新建 wpa_supplicant.conf 文件，按照下面的参考格式填入内容并保存 wpa_supplicant.conf 文件。
```
country=CN
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
 
network={
ssid="WiFi-A"
psk="12345678"
key_mgmt=WPA-PSK
priority=1
}

* 使用公钥链接服务器  `ssh -i "xxx.pem" name@0.0.0.0`

* VNS 相关 [BBR](https://xiaozhou.net/enable-bbr-for-vps-2017-06-10.html); [配置](https://yizibi.github.io/2018/10/24/%E8%B6%85%E8%AF%A6%E7%BB%86%E5%9B%BE%E6%96%87%E5%85%8D%E8%B4%B9%E6%90%AD%E5%BB%BAVPS,VPN%E9%85%8D%E7%BD%AE/); [参考](https://starorc.gitbooks.io/set-up-ss/content/set_up_ss/set_sv.html)

```

# samba 与 MiniDLNA

[link](https://www.jianshu.com/p/7dc8f2a01c27)

# vim常用命令

* 赋值粘贴 

```
1. 将光标移动到要复制的文本开始的地方，按v进入可视模式。
2. 将光标移动到要复制的文本的结束的地方，按y复制。此时vim会自动将光标定位到选中文本的开始的地方，并退出可视模式。
3. 移动光标到文本结束的地方，按p粘贴

```


# ffmpeg

* 下载 `ffmpeg -i https://ddppnew1.135-cdn.com/20190415/TOQuy5vq\/index.m3u8 -c copy -bsf:a aac_adtstoasc 1.mkv`