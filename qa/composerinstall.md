## How to install composer in Ubuntu [Back](./qa.md)

- To download composer:

```bash
curl -sS https://getcomposer.org/installer | php
```

- Install composer:

```bash
/usr/bin/php composer.phar --version
```

- Set global variable:

```bash
sudo mv composer.phar /usr/local/bin/composer
```

- Check whether install successfully:

```bash
composer --version
```
