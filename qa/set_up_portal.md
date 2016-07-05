## Set up portal with WifiDog + AuthPuppy [Back](./qa.md)

- Router Firmware: **OpenWRT/DDWRT**
- Gateway: **WifiDog**
- Auth Server: **AuthPuppy**

### Installation of AuthPuppy

i. Download AuthPuppy from https://launchpad.net/authpuppy

ii. Unzip the file

```bash
tar -zxvf authpuppy-1.0.0-stable.tgz
```

iii. Move `authpuppy/` to `/var/www`

```bash
mv authpuppy /var/www/
```

iv. Change authority owner

```bash
chown -R www-data:www-data /var/www/authpuppy
```

v. Create mysql

vi. Create Apache/Nginx

- Website Path: `/var/www/authpuppy/web`
- Bind domain name: `auth.blackmagic.science`
- Start `url rewrite`

vii. Open http://auth.blackmagic.science/ to start installation

### Create a new node for a router

Login to authpuppy to create nodes for each router:

- Name
- gw id: Gateway id
- Deployment status: deployed
- Optional

### Configuration of routers

i. Install WifiDog

- OpenWRT: `opkg install wifidog`
- DDWRT: has been installed by default

ii. Configure WifiDog

```bash
# vim /etc/wifidog.conf
AuthServer {
    Hostname auth.blackmagic.science
    SSLAvailable no
    Path /
}
```

iii. Start WifiDog

```bash
/etc/init.d/wifidog enable

# or

/etc/init.d/wifidog start
```