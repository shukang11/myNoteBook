# nginx 配置

## 安装 

` apt install nginx `


## 自定义配置

` cd /etc/nginx/conf.d/ `

新建配置文件

```
# pandaMama server config

server {
        server_name _; // 服务器名称
        listen 5000; // 监听的端口号
        location / {
                proxy_set_header Connection "";
                proxy_set_header X-Real-IP $remote_addr;
                proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
                proxy_set_header Host $http_host;
                proxy_set_header X-NginX-Proxy true;
                proxy_pass http://127.0.0.1:6000;
                proxy_redirect off; // 重定向开关
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
~

```

## 常用命令

重新加载 `nginx -s reload`