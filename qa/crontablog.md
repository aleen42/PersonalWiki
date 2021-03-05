## How to see logs of crontab in Ubuntu [Back](./qa.md)

#### 1. setup the logs of crontab

```sh
# sudo vim /etc/rsyslog.d/50-default.conf
# remove the '#' before cron.*  /var/log/cron.log

cron.*              /var/log/cron.log
```

#### 2. restart the server

```sh
sudo  service rsyslog  restart
```

#### 2. see the logs

```sh
vim /var/log/cron.log 
```
