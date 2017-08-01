## Lunkr + Coremail	[Back](./../coremail.md)

This article is mainly used for deploying Lunkr servers with Coremail.

### 1. Deploy a Lunkr server

The installation package is on the filer:

`\\192.168.209.6\qc\cim\release\01.Lunkr\10.other\03.论客程序包`

Firstly, access the server and download the latest Lunkr package for installation, like `lunkr.bak.20170222.tgz`:

Then, upload the package to the server which you want to install into.

Before installing the package, you may also need to backup your local Coremail as the package will install another one to override it:

1. Stop all the served applications firstly, including MySQL:
    ```bash
    /home/coremail/sbin/cmctrl.sh stop all
    ```
2. Back up the original Coremail package:
    ```bash
    tar zcvf /home/coremail.bak.tgz /home/coremail
    ```

After that, just remove the original Coremail package:

```bash
sudo rm -rf /home/coremail
```

Then release the Lunkr package you have uploaded before:

```bash
tar zxvf /home/lunkr.bak.tgz -C /home
```

After that, just start all served applications:

```bash
/home/coremail/sbin/cmctrl.sh start all
```

### 2. 