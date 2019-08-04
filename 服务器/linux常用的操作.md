# 索引

* [挂载硬盘](#挂载硬盘)

* [无屏幕配置树莓派wifi连接](#无屏幕配置树莓派wifi连接)

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

```