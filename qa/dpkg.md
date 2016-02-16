## How to solve the problem of dpkg sub-process throwing a error in Ubuntu [Back](./qa.md)

- Sometimes, you'll find that there's a error when using apt-get to install library. Like the follow:

```bash
E: Sub-process /usr/bin/dpkg returned an error code (1)
```

- **Solution**:

```bash
# backup the info directory
sudo mv /var/lib/dpkg/info /var/lib/dpkg/info.bak


```

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
