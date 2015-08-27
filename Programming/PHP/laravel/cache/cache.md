## Cache [Back](./../PHP.md)

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


<a href="#" style="left:200px;"><img src="./../../../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../../pic/tail.gif"></a>