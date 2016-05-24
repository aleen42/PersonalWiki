## Cache [Back](./../laravel.md)

### Configuration

- The cache configuration file is located at **./config/cache.php**.
- Laravel supports popular caching backends like **Memcached** and **Redis** out of the box.
- By default, Laravel is configured to use the **file** cache driver, which stores the **serialized**, cached objects in the filesystem.
- For larger applications, it is recommended that you use an **in-memory cache** such as Memcached or APC.

#### Cache Prerequisites(先決條件)

##### Database

- When using the **database** cache driver, you'll need to setup a table to contain the cache items.

```php
Schema::create('cache', function($table){
	$table->string('key')->unique();
	$table->text('value');
	$talbe->integer('expiration');
});
```

##### Memcached

- Using the Memcached cache requires the [**Memcached PECL package**](http://pecl.php.net/package/memcached) to be installed.
- The default configuration uses TCP/IP based on Memcached::addServer.

```php
'memcached' => [
    [
        'host' => '127.0.0.1',
        'port' => 11211,
        'weight' => 100
    ],
],
```

- You may also set the host option to a UNIX socket path. If you do this, the port option should be set to **0**.

```php
`memcached` => [
	[
		'host' => '/var/run/memcached/memcached.sock',
		'port' => 0,
		'weight' => 100
	],
],
```

##### Redis

- Before using a Redis cache with Laravel, you will need to install the **predis/predis** package (~1.0) via Composer.
