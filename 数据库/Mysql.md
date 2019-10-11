# MySql

##  基本用法

* 增删改查

* 子查询
> SQL还允许创建子查询(subquery)，即嵌套在其他查询中的查询

``` 
SELECT some_field FROM a_table WHERE field IN (
    SELECT another_field FROM b_table WHERE field IN (
        1000, 12203
    )
);
```

* 联结表
> 分解多个表可以更高效的储存，具有更强的伸缩性

```
SELECT bao_rss.rss_id, bao_rss_content.content_id, bao_rss_content.content_link 
FROM bao_rss_content INNER JOIN bao_rss ON bao_rss_content.content_base=bao_rss.rss_link;

```

```
SELECT bao_rss_user.user_id, bao_rss.rss_id, bao_rss_content.content_id FROM bao_rss_content, bao_rss, bao_rss_user
    WHERE bao_rss_content.content_link='link' 
        AND bao_rss_content.content_base=bao_rss.rss_link 
        AND bao_rss.rss_id=bao_rss_user.rss_id 
        AND bao_rss_user.user_id=1;

```

## Mysql Tips

* 执行外部 sql 文件

`mysql -u root -p -D database<path/to/sql_file.sql`

* 开启 3306 端口

- 查看端口占用情况 `netstat -an | grep 3306`

- 查看端口号 `show global variables like 'port';`

- 更新root用户的host `use mysql; update user set host='%' where user='root'; flush privileges;`

- 修改配置文件
```
[mysqld]
port=3306
bind-address=0.0.0.0
```