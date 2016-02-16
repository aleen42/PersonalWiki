## How to solve the problem of dpkg sub-process throwing a error in Ubuntu [Back](./qa.md)

- Sometimes, you'll find that there's a error when using apt-get to install library. Like the follow:

```bash
E: Sub-process /usr/bin/dpkg returned an error code (1)
```

- **Solution**:

```bash
# backup the info directory
sudo mv /var/lib/dpkg/info /var/lib/dpkg/info.bak

# create a new directory
sudo mkdir /var/lib/dpkg/info

# update apt-get
sudo apt-get update

# install what you want to install
apt-get -f install xxx

# mv all the files under the new directory to the old backup
sudo mv /var/lib/dpkg/info/* /var/lib/dpkg/info.bak
```

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
