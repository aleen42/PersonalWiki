## Redis	[Back](./../summary.md)

<img src="./logo.png">

### Menu

- [**1. Introduction**](#1)
- [**2. Commands**](#2)
- [**3. Usages in PHP**](#3)
- [**4. Usages in Laravel**](#4)

<br />
<br />
<br />
<br />
<br />
<br />

<h3 id="1"> 1. Introduction</h3>
===

- Redis is an open source (BSD licensed), in-memory **data structure store**, used as database, cache and message broker.
- It supports data strucures such as **strings**(字符串), **hashes**(哈希), **lists**(列表), **sets**(集合), **sorted sets**(有序集合) with range queries, **bitmaps**(位圖), **hyperloglogs** and **geospatial indexes** with radius queries. 
- 6 strategies(策略) of Redis:
	- 1. volatile-lru: 從已設置過期的數據集(`server.db[i].expires`)中挑選最近最少使用的數據淘汰.
	- 2. volatile-ttl: 從已設置過期的數據集(`server.db[i].expires`)中挑選將要過期的數據淘汰.
	- 3. volatile-random: 從已設置過期時間的數據集(`server.db[i].expires`)中任意選擇數據淘汰.
	- 4. allkeys-lru: 從數據集(`server.db[i].dict`)中挑選最近最少使用的數據淘汰.
	- 5. allkeys-random: 從數據集(`server.db[i].dict`)中任意選擇數據淘汰.
	- 6. no-enviction(驅逐): 禁止驅逐數據.

<br />
<br />
<br />
<br />
<br />
<br />

<h3 id="2"> 2. Commands</h3>
===

##### 2.1 EXISTS key [key ...]

- Description: To search whether multiple keys are existed.
- Return:
	- **1**: if the key exists.
	- **0**: if the key does not exist.
	- The number of keys existing among the ones specified as arguments. Keys mentioned multiple times and existing are counted multiple times. (**Since Redis 3.0.3**)
- Example:

	```redis
redis> SET key1 "Hello"
OK
redis> EXISTS key1
(integer) 1
redis> EXISTS nosuchkey
(integer) 0
redis> SET key2 "World"
OK
redis> EXISTS key1 key2 nosuchkey
(integer) 2
redis> 
```


##### 2.2 APPEND key value

- Description: If key already exists and is a string, this command appends the value at the end of the string. If **key** does not exist it is created and set as an empty string.
- Return: The length of the value.
- Example:

	```redis
redis> EXIST mykey
(integer) 0
redis> APPEND mykey
(integer) 0
redis> APPEND mykey "Hello"
(integer) 5
redis> APPEND mykey " World"
(integer) 11
redis> GET mykey
"Hello World"
redis>
```

##### 2.3 DEL key [key ...]

- Description: To delete keys.
- Return: The number of keys that were removed.
- Example:

	```redis
redis> SET key1 "Hello"
OK
redis> SET key2 "World"
OK
redis> DEL key1 key2 key3
(integer) 2
redis> 
```

##### 2.4 SET key value [EX seconds] [PX milliseconds] [NX|XX]

- Description: Set key to hold the string value. If key already holds a value, it is overwritten, regardless of its type.
- Options:
	- **EX** (seconds): Set the specified expire time, in seconds.
	- **PX** (milliseconds): Set the specified expire time, in milliseconds.
	- **NX**: Only set the key if it does not already exist.
	- **XX**: Only set the key if it already exist.
- Return: 
	- **OK**: if SET was executed correctly.
	- **(nil)**: a Null Bulk Reply is returned if the SET operation was not performed because the user specified the NX or XX option but the condition was not met.
- Example:

	```redis
redis> SET mykey "Hello"
OK
redis> GET mykey
"Hello"
redis>  
```


##### 2.5 GET key

- Description: Get the value of key.
- Return: 
	- **Value**: the value of key.
	- **(nil)**: a Null Bulk Reply is returned if the key does not exist.
- Example:

	```redis
redis> GET nonexisting
(nil)
redis> SET mykey "Hello"
OK
redis> GET mykey
"Hello"
redis>
```

##### 2.6 KEYS pattern

- Description: Returns all keys matching pattern.
- Options: pattern (Use `\` to escape special characters if you want to match them verbatim.)
	- **h?llo**: matches **hello**, **hallo** and **hxllo**.
	- **h\*llo**: matches **hllo**, **hxxxxxxxxxllo**.
	- **h[ae]llo**: matches **hello** and **hallo**, but not **hillo**.
	- **h[^e]llo**: matches **hallo**, **hbllo**, ... but not **hello**.
	- **h[a-c]llo**: matches **hallo**, **hbllo** and **hcllo**.
- Return: list of keys matching pattern.
- Example:

	```redis
redis> GET nonexisting
(nil)
redis> SET mykey "Hello"
OK
redis> GET mykey
"Hello"
redis>
```

##### 2.7 INCR key

- Description: Increments the number stored at key by one.
- **Note**: This is a string operation because Redis does not have a dedicated integer type. The string stored at the key is interpreted as a base-10 **64 bit signed integer** to execute the operation.
- Return: the value of key after the increment.
- Example:

	```redis
redis> SET mykey "10"
OK
redis> INCR mykey
(integer) 11
redis> GET mykey
"11"
redis> 
```

##### 2.8 DECR key

- Description: Decrements the number stored at key by one.
- **Note**: This operation is limited to **64 bit signed integers**.
- Return: the value of key after the decrement.
- Example:

	```redis
redis> SET mykey "10"
OK
redis> DECR mykey
(integer) 9
redis> SET mykey "234293482390480948029348230948"
OK
redis> DECR mykey
ERR value is not an integer or out of range
redis>  
```

##### 2.9 INCRBY key increment

- Description: Increments the number stored at key by increment.
- **Note**: An error is returned if the key contains a value of the wrong type or contains a string that can not be represented as integer.
- Return: the value of key after the increment.
- Example:

	```redis
redis> SET mykey "10"
OK
redis> INCRBY mykey 5
(integer) 15
redis> 
```

##### 2.10 DECRBY key decrement

- Description: Decrements the number stored at key by decrement.
- **Note**: An error is returned if the key contains a value of the wrong type or contains a string that can not be represented as integer.
- Return: the value of key after the decrement.
- Example:

	```redis
redis> SET mykey "10"
OK
redis> DECRBY mykey 3
(integer) 7
redis> 
```

<h5> 2.11 <a href="http://redis.io/commands" target="_blank"><strong>More Commands</strong></a></h5>

<br />
<br />
<br />
<br />
<br />
<br />

<h3 id="3"> 3. Usages in PHP</h3>
===

##### 3.1 Connect

- Description: Connect to a **redis**.
- Return: 
	- **true**: success
	- **false**: failure
- Example:

	```php
<?php  
$redis = new redis();  
$result = $redis->connect('127.0.0.1', 6379);  
var_dump($result);	// bool(true)  
?>  
```

##### 3.2 Set

- Description: set the **value** of a key.
- Return: 
	- **true**: success
	- **false**: failure
- Example:

	```php
<?php  
$redis = new redis();  
$redis->connect('127.0.0.1', 6379);  
$result = $redis->set('test',"11111111111");  
var_dump($result);	// bool(true)
?>  
```

##### 3.3 Get

- Description: get the **value** of a key.
- Return: 
	- **value**: the value of the specific key
	- **false**: key does not exist
- Example:

	```php
<?php  
$redis = new redis();  
$redis->connect('127.0.0.1', 6379);  
$result = $redis->set('test',"11111111111");  
var_dump($result);	// string(11) "11111111111"
?>  
```

##### 3.4 Delete

- Description: to delete the key.
- Options: an array of keys
- Return: 
	- **value**: the number of deleted keys
- Example:

	```php
<?php  
$redis = new redis();  
$redis->connect('127.0.0.1', 6379);  
$redis->set('test',"1111111111111");  
echo $redis->get('test');   // 1111111111111  
$redis->delete('test');  
var_dump($redis->get('test'));  // bool(false)  
?>   
```

##### 3.5 Set, Setnx, Setxx

- Description: to set the value of a key
- Return: 
	- **true**: success
	- **false**: failure
- Example:

	```php
<?php  
$redis = new redis();  
$redis->connect('127.0.0.1', 6379);  
$redis->set('test',"1111111111111");  
$redis->setnx('test',"22222222");  
echo $redis->get('test');  // 1111111111111  
$redis->delete('test');  
$redis->setnx('test',"22222222");  
echo $redis->get('test');  // 22222222  
?>  
```

##### 3.6 Exists

- Description: to whether a key is existed
- Return: 
	- **true**: success
	- **false**: failure
- Example:

	```php
<?php  
$redis = new redis();  
$redis->connect('127.0.0.1', 6379);  
$redis->set('test',"1111111111111");  
var_dump($redis->exists('test'));  // bool(true)  
?> 
```

##### 3.7 Incr

- Description: to increase the value of a key by one.
- Return: the new value after the increment
- Example:

	```php
<?php  
$redis = new redis();  
$redis->connect('127.0.0.1', 6379);  
$redis->set('test',"123");  
var_dump($redis->incr("test"));  // int(124)  
var_dump($redis->incr("test"));  // int(125)  
?> 
```

##### 3.8 Decr

- Description: to decrease the value of a key by one.
- Return: the new value after the decrement
- Example:

	```php
<?php  
$redis = new redis();  
$redis->connect('127.0.0.1', 6379);  
$redis->set('test',"123");  
var_dump($redis->decr("test"));  // int(122)  
var_dump($redis->decr("test"));  // int(121)  
?>
```

<h5> 3.9 <a href="http://www.jb51.net/article/51884.htm" target="_blank"><strong>More Usages</strong></a></h5>

<br />
<br />
<br />
<br />
<br />
<br />

<h3 id="4"> 4. Usages in Laravel</h3>
===

##### 4.1 
