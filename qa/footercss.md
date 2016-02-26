## How to write footer with CSS [Back](./qa.md)

- By default, server will only allow local accessing mysql server, which will cause the problem of Navicat connection.

#### Solution

i. Configure the mysql of your server

```bash
# vim /etc/mysql/my.cnf

[mysqld]
# ...
# add comment for bind-address and add skip-networking after it.
# bind-adress    = 127.0.0.1
# skip-networking
```

ii. Store and restart the service

```bash
service mysql restart
```

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
