## How to deploy a shadowsocks server on a Vultr VPS [Back](./qa.md)

### 1. Install Shadowsocks via script

Here we are going to use the script of [teddysun](https://teddysun.com/342.html) to install servers of Shadowsocks on the Vultr VPS server automatically:

At first, download the script:

```bash
wget --no-check-certificate https://raw.githubusercontent.com/teddysun/shadowsocks_install/master/shadowsocks.sh
chmod +x shadowsocks.sh
```

Then change mode of this file to give it privilege to run:

```bash
chmod +x shadowsocks.sh
```

Finally run it:

```bash
./shadowsocks.sh 2>&1 | tee shadowsocks.log
```
