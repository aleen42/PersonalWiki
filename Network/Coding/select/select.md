## Select [Back](./../Coding.md)

- to support multiplexing
- multiplex means to use one channel to transmit several signals
	- WDM (波分複用): 按照頻率來區分各路信號
	- TDM (時分複用): 按照時間片來區分各路信號
- **select()** is to check several socket descriptors, and return when one is ready for multiplexing
- 可用於監聽多個進程(多個文件描述符)

### 1. select()
##### method

```c
/* select */
int select(int maxfd, fd_set* rdset, fd_set* wrset, fd_set* exset, struct timeval* timeout)

/* timeval */
struct timval
{
	long tv_sec;	//second
	long tv_usec;	//millisecond
}

```

##### parameters
- maxfd: 需要測試的描述符集合中的最大值 + 1, 實際是測試[0, maxfd-1]
- rdset: 需要測試是否可讀的描述符集合(包括處於listen狀態的socket接收到鏈接請求)
- wrset: 需要測試是否可寫的描述符集合(包括以非阻塞方式調用connect是否成功)
- exset: 需要測試是否異常的描述符集合(包括接受帶外數據的socket有带外数据到達)
- timeout: 指定測試時間閾值上界
	- NULL: forever
	- \>0: time
	- 0: return immediately after check, without waiting

##### return value
- num: the number of ready descriptors
- 0: timeout but none is ready
- -1: failure
- errno: wrong code

### 2. Operations with sets of  socket descriptors
- ```FD_ZERO(fd_set* fdset)```清空描述符集合
- ```FD_SET(int fd, fd_set* fdset)```添加一個描述符到描述符集合
- ```FD_CLR(int fd, fd_set* fdset)```從描述符集合刪除一个描述符
- ```FD_ISSET(int fd, fd_set* fdset)```檢測一個描述符是否存在於描述符集合
