## How to enable MySQL logs and watch them [Back](./qa.md)

Here is a simple way to enable MySQL logs. There are 3 types of logs in MySQL:

- **Error Log**: It contains information about errors that occur while the server is running (also server start and stop)
- **General Query Log**: This is a general record of what mysqld is doing (connect, disconnect, queries)
- **Slow Query Log**: Ιt consists of "slow" SQL statements (as indicated by its name).

By default no log files are enabled in MYSQL. All errors will be shown in the syslog.(/var/log/syslog)

To Enable them just follow below steps

**step1**: Go to this file(/etc/mysql/conf.d/mysqld_safe_syslog.cnf) and remove or comment those line.

**step2**: Go to mysql conf file(/etc/mysql/my.cnf ) and add following lines