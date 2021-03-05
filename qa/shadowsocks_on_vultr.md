## How to deploy a shadowsocks server on a Vultr VPS [Back](./qa.md)

### 1. Install Shadowsocks via script

Here we are going to use the script of [teddysun](https://teddysun.com/342.html) to install servers of Shadowsocks on the Vultr VPS server automatically:

At first, download the script:

```bash
wget --no-check-certificate https://raw.githubusercontent.com/teddysun/shadowsocks_install/master/shadowsocks.sh
```

Then change mode of this file to give it privilege to run:

```bash
chmod +x shadowsocks.sh
```

Finally run it:

```bash
./shadowsocks.sh 2>&1 | tee shadowsocks.log
```

If you want to install ShadowsocksR, just download the mirror like the following snippet:

```bash
wget --no-check-certificate https://raw.githubusercontent.com/teddysun/shadowsocks_install/master/shadowsocksR.sh
```

### 2. Set the password

<p align="center">
  <img alt="set_password" title="mingtocat" src="./shadowsocks1.jpeg" width="60%" />
</p>

### 3. Set the port

<p align="center">
  <img alt="set_port" title="mingtocat" src="./shadowsocs2.jpg" width="60%" />
</p>

### 4. Select specific encryption method

According to [the document](https://github.com/shadowsocks/libQtShadowsocks/wiki/Comparison-of-Encryption-Methods'-Speed), there is a comparison of encryption methods' speed, testing with 100MB datagram size.

1. **x86 + Intel Core i7-6500U**

    | Encryption Methods | Time Used (ms) |
    |-------------------:|:--------------:|
    |        aes-128-cfb |      639       |
    |        aes-192-cfb |      693       |
    |        aes-256-cfb |      764       |
    |             bf-cfb |      1103      |
    |   camellia-128-cfb |      1038      |
    |   camellia-192-cfb |      1261      |
    |   camellia-256-cfb |      1266      |
    |          cast5-cfb |      1213      |
    |           chacha20 |      307       |
    |            des-cfb |      1613      |
    |           idea-cfb |      2066      |
    |            rc2-cfb |      2214      |
    |            rc4-md5 |      551       |
    |            salsa20 |      263       |
    |           seed-cfb |      1521      |
    |        serpent-cfb |      1444      |
2. **x86 + AMD Phenom II X4 N930**

    | Encryption Methods | Time Used (ms) |
    |-------------------:|:--------------:|
    |        aes-128-cfb |      1860      |
    |        aes-192-cfb |      1984      |
    |        aes-256-cfb |      2125      |
    |             bf-cfb |      2563      |
    |   camellia-128-cfb |      3812      |
    |   camellia-192-cfb |      4797      |
    |   camellia-256-cfb |      4828      |
    |          cast5-cfb |      2766      |
    |           chacha20 |      687       |
    |            des-cfb |      3563      |
    |           idea-cfb |      4562      |
    |            rc2-cfb |      5219      |
    |            rc4-md5 |      2640      |
    |            salsa20 |      875       |
    |           seed-cfb |      2657      |
    |        serpent-cfb |      2875      |
3. **ARM + Samsung Exynos 4412 Prime**

    | Encryption Methods | Time Used (ms) |
    |-------------------:|:--------------:|
    |        aes-128-cfb |      3837      |
    |        aes-192-cfb |      4089      |
    |        aes-256-cfb |      4443      |
    |             bf-cfb |      4320      |
    |   camellia-128-cfb |      5920      |
    |   camellia-192-cfb |      7058      |
    |   camellia-256-cfb |      7057      |
    |          cast5-cfb |      4730      |
    |           chacha20 |      1297      |
    |            des-cfb |      8147      |
    |           idea-cfb |      6678      |
    |            rc2-cfb |      8846      |
    |            rc4-md5 |      3170      |
    |            salsa20 |      1666      |
    |           seed-cfb |      6941      |
    |        serpent-cfb |      4440      |

### 5. TCP Fast Open

To enhance the speed of connection, you can do more with followed steps:

1. Add the followed line into the file `/etc/rc.local`:
    ```bash
    # /etc/rc.local
    echo 3 > /proc/sys/net/ipv4/tcp_fastopen
    ```
2. Add the followed line into the file `/etc/sysctl.conf`:
    ```bash
    # /etc/sysctl.conf
    net.ipv4.tcp_fastopen = 3
    ```
3. Modified the attribute `fast_open` with `true` in the file `/etc/shadowsocks.json`
4. Restart the server of Shadowsocks:
    ```bash
    /etc/init.d/shadowsocks restart
    ```
