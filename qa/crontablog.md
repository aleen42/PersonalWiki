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

<a href="#how-to-use-gitbook-to-write-something" style="left:200px;"><img src="./../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
