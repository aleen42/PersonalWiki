## IO(輸入/輸出)	[Back](./../OS.md)

- Linux系統下**I/O模型**:
	- 阻塞式I/O
	- 非阻塞式I/O
	- 多路複用I/O
	- 信號驅動I/O

### 1. 阻塞式IO

- 結構簡單, 容易同步
- 阻塞導致CPU資源浪費
- 通過調用```alarm()```來進行超時控制
	- 超時到達時產生SIGALARM信號中斷阻塞
	- 多次調用時則無法區分SIGALARM信號是哪一次超時引發, 從而導致無法實現超時控制
- 通過設置socket選項進行超時控制
	- 設置SO_RCVTIMEO和SO_SNDTIMEO
	- 只需設置一次, 對後來的讀寫操作均有效
	- 不適用於accept和connect

##### 1.1 Read
 
<img src="./blocking_io_read.png">

- 產生阻塞的函數:
	- ```read()```
	- ```readv()```
	- ```recv()```
	- ```recvfrom()```
	- ```recvmsg()```

- 進程喚醒的狀態:
	- TCP以**字節**為單位, 只要接收緩衝區出現數據則喚醒
	- UDP以**數據報**為單位, 當完整的數據報到達才喚醒

##### 1.2 Write

<img src="./blocking_io_write.png">

- 產生阻塞的函數:
	- ```write()```
	- ```writev()```
	- ```send()```
	- ```sendto()```
	- ```sendmsg()```

- UDP協議寫操作永遠不會阻塞

##### 1.3 Connect

<img src="./blocking_io_connect.png">

- 產生阻塞的函數:
	- ```connect()```

- TCP下, Client收到Server的SYN字段則表示```connect()```成功.
- TCP連接操作至少需要一個往返時間
- UDP沒有連接, 故不產生阻塞

##### 1.4 Accpet

<img src="./blocking_io_accept.png">

- 產生阻塞的函數:
	- ```accept()```

### 2. 非阻塞式IO

<img src="./disblocking_io.png">

- 設置socket為非阻塞方式
	- ```fcntl()```
	
	```c
	int flags;
	flag = fcntl(sockfd, F_GETFL, 0);
	fcntl(sockfd, F_SETFL, flat| O_NONBLOCK);
	```
	- ```ioctl```
	
	```c
	int on = 1;
	ioctl(sockfd, FIONBIO, &on);
	```

<a href="#" style="left:200px;"><img src="./../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
