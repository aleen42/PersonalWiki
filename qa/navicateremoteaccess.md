## How to enable Navicat with remote accessing database [Back](./qa.md)

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
iii. Allow access with IP 10.10.50.127

```mysql
GRANT ALL PRIVILEGES ON *.* TO 'root'@'10.10.50.127' IDENTIFIED BY "password" WITH GRANT OPTION;
FLUSH PRIVILEGES;
```

iv. Allow access with different IP

```mysql
GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' IDENTIFIED BY "password" WITH GRANT OPTION;
FLUSH PRIVILEGES;
```