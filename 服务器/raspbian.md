# raspbian

#### 写入系统

### 1. sd卡插入读卡器并查看磁盘序号

`diskutil list`

### 2.移除挂载的盘 

`diskutil unmountDisk <disk>`

### 3.写入镜像

`sudo dd bs=1m if=xxxxx.img of=/dev/rdiskn conv=sync`
