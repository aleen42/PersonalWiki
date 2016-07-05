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