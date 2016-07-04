## How to free cached memory in Ubuntu [Back](./qa.md)

*Note: **Linux is NOT "eating" your RAM! Please take a look at Geirha's [excellent answer](http://askubuntu.com/a/155771/58612) below to understand why...***

After the above note, if you still feel "cleaning" the cache could help, you can certainly try: it's a one-liner from the terminal:

```bash
sync && echo 3 | sudo tee /proc/sys/vm/drop_caches
```

Get real free ram without cached:

```bash
free -m | sed -n -e '3p' | grep -Po "\d+$"
```




