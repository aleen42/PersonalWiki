## How to set ssh with asymmetric keys on servers [Back](./qa.md)

### 1. Generate asymmetric keys **private/public**

#### Linux/Mac

```bash
ssh-keygen -t ed25519 -o -a 100 -C "comment here"
ssh-keygen -t rsa -b 4096 -o -a 100 -C "comment here"
```

- **t**: types of key
- **C**: used to tag who the certification belongs to
- **passphrase**: the password to protect private key, which can be empty.

*Notice that: In general, keys will be saved in the `.ssh` directory of the root, in which `id_rsa` is the private one while `id_rsa.pub` is the public one*

#### Windows

In Windows, we can use **PuTTY** to generate private/public keys:

<img src="./ssh-puttykey.png">

SSH-2 RSA is the default type of keys and number of bits should be **4096** nowadays.

### 2. Configure ssh on the server

Generally, servers will use SSH login servers provided by OpenSSH, and we should configure it with modifying `sshd_config`

In CentOS and Ubuntu, this file should be in `/etc/ssh/`

```bash
vim /etc/ssh/sshd_config
```

#### Port

Port is **22** by default, and it's suggested that we should change it to a number between **2001** and **65534**

*Notice that: after changing the port, you should add new port to the white list when firewall is opened like iptables or FirewallD in CentOS*

```bash
firewall-cmd --zone=public --add-port=2222/tcp --permanent
```