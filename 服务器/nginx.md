# nginx 配置

*  ## nginx架构

nginx启动后，在unix系统中以daemon的方式在后台运行，包含了一个master与若干个worker进程，master主要是来管理worker的，包含：接收来自外界的信号，向各worker进程发送信号，监控worker进程的运行状态，当worker进程退出后(异常情况下)，会自动重新启动新的worker进程。

当我们提供80端口的http服务时，一个连接请求过来，每个进程都有可能处理这个连接，怎么做到的呢？首先，每个worker进程都是从master进程fork过来，在master进程里面，先建立好需要listen的socket（listenfd）之后，然后再fork出多个worker进程。所有worker进程的listenfd会在新连接到来时变得可读，为保证只有一个进程处理该连接，所有worker进程在注册listenfd读事件前抢accept_mutex，抢到互斥锁的那个进程注册listenfd读事件，在读事件里调用accept接受该连接。当一个worker进程在accept这个连接之后，就开始读取请求，解析请求，处理请求，产生数据后，再返回给客户端，最后才断开连接，这样一个完整的请求就是这样的了。我们可以看到，一个请求，完全由worker进程来处理，而且只在一个worker进程中处理。

## 安装 

` apt install nginx `


## 自定义配置

` cd /etc/nginx/conf.d/ `

如果是 mac ，那么配置地址则是 ` cd /usr/local/etc/nginx/conf.d/ `

新建配置文件

```
# pandaMama server config

server {
        listen      443 ssl; # 开启 443 端口监听 开启 https
        ssl_certificate cert/a.pem; # 证书地址
        ssl_certificate_key cert/a.key; 
        server_name _; # 服务器名称
        listen 5000; # 监听的端口号
        location / {
                proxy_set_header Connection ""; # 设置请求头信息
                proxy_set_header X-Real-IP $remote_addr;
                proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
                proxy_set_header Host $http_host;
                proxy_set_header X-NginX-Proxy true;
                proxy_pass http://127.0.0.1:6000; # 转发到本机端口
                proxy_redirect off; # 重定向开关1
        }
}

```



```
server {
        server_name _;
        listen 5001;
        location / {
                root /www/modular-admin-html/dist; # 指向静态的地址
                index index.html; # 指定 index 文件
        }
}

```
* 这里配置的静态文件，但是有时会出现`403`错误,需要检查nginx的配置 user 选项，是否分配了一个有权限的用户或用户组

## 常用命令

重新加载 `nginx -s reload`