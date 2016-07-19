## How to enable MySQL logs and watch them [Back](./qa.md)

Here is a simple way to enable MySQL logs. There are 3 types of logs in MySQL:

- **Error Log**: It contains information about errors that occur while the server is running (also server start and stop)
- **General Query Log**: This is a general record of what mysqld is doing (connect, disconnect, queries)
- **Slow Query Log**: Ιt consists of "slow" SQL statements (as indicated by its name).

By default no log files are enabled in MYSQL. All errors will be shown in the syslog.(/var/log/syslog)

To Enable them just follow below steps

**step1**: Go to this file(/etc/mysql/conf.d/mysqld_safe_syslog.cnf) and remove or comment those line.

**step2**: Go to mysql conf file(/etc/mysql/my.cnf ) and add following lines

###### To enable error log by adding following lines:

```
[mysqld_safe]
log_error=/var/log/mysql/mysql_error.log

[mysqld]
log_error=/var/log/mysql/mysql_error.log
```

###### To enable general query log by adding following lines:

```
general_log_file        = /var/log/mysql/mysql.log
general_log             = 1
```

###### To enable slow query log by adding following lines:

```
log_slow_queries       = /var/log/mysql/mysql-slow.log
long_query_time = 2
log-queries-not-using-indexes
```

**step3**: save the file and restart mysql using following commands:

```bash
service mysql restart
```

###### To enable logs at runtime, login to mysql client (mysql -u root -p ) and give:

```sql
SET GLOBAL general_log = 'ON';
SET GLOBAL slow_query_log = 'ON';
```