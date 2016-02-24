## Hot to enable navicat with remote accessing database [Back](./qa.md)

- By default, server will only allow local accessing mysql server, which will cause the problem of Navicat connection.

#### Solution

1. Configure the mysql of your server

```bash
# vim /etc/mysql/my.cnf

[mysqld]
# ...
# add comment for bind-address and add skip-networking after it.
# bind-adress    = 127.0.0.1
# skip-networking
```

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
