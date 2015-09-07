## Redis	[Back](./../summary.md)

<img src="./logo.png">

### Menu

- [**1. Introduction**](#1)
- [**2. Commands**](#2)
- [**3. Usage in PHP**](#3)

<br />
<br />
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

<h5> 2.7 <a href="http://redis.io/commands" target="_blank"><strong>More Commands</strong></a></h5>

<h3 id="3"> 3. Usage in PHP</h3>
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
var_dump($result);  
?>  
```



<a href="#" style="left:200px;"><img src="./../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
