## Redis	[Back](./../summary.md)

<img src="./logo.png">

### 1. Introduction

- Redis is an open source (BSD licensed), in-memory **data structure store**, used as database, cache and message broker.
- It supports data strucures such as **strings**, **hashes**, **lists**, **sets**, **sorted sets** with range queries, **bitmaps**, **hyperloglogs** and **geospatial indexes** with radius queries. 
- 6 strategies(策略) of Redis:
	- 1. volatile-lru: 從已設置過期的數據集(`server.db[i].expires`)中挑選最近最少使用的數據淘汰.
	- 2. volatile-ttl: 從已設置過期的數據集(`server.db[i].expires`)中挑選將要過期的數據淘汰.
	- 3. volatile-random: 從已設置過期時間的數據集(`server.db[i].expires`)中任意選擇數據淘汰.
	- 4. allkeys-lru: 從數據集(server.db[i].dict)中挑選最近最少使用的數據淘汰.
	- 5. allkeys-random: 從數據集(server.db[i].dict)中任意選擇數據淘汰.
	- 6. no-enviction(驅逐): 禁止驅逐數據.

### 2. Command

#### 2.1 Key

##### 2.1.1 EXISTS

- Description: To search whether multiple keys are existed.
- Return:
	- 1: if the key exists.
	- 0: if the key does not exist.
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


##### 2.1.2 APPEND

- Description: If **key** already exists and is a string, this command appends the value at the end of the string. If **key** does not exist it is created and set as an empty string.
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



<a href="#" style="left:200px;"><img src="./../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
