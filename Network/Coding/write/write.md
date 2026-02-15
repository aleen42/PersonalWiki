## Write [Back](./../Coding.md)

- to send data
- write method will be **blocked** buffer is too smaller to send data of len, until one of three situations has happened:
	- buffer is enough
	- connection is reset, return **error**
	- received a signal of interruption, return **error** (errno = EINTR)

### 1. write()
##### method

```c
int write(int fd, char* buf, int len)
```

##### parameters
- fd: socket描述符
- buf: 發送緩衝區
- len: 要發送數據的長度

##### return value
- \>=0: success
	- **len**: the length of buffer is greater than len

- -1: failure
- errno: wrong code

### 2. send()
##### method

```c
int send(int sockfd, void buf, int len, int flags)
```

##### parameters
- fd: socket描述符
- buf: 接受緩衝區
- len: 接受數據長度
- flags: 接受數據的控制參數
	- 0: read()
	- MSG_DONTROUTE: 發送數據時不查找路由表, 適用於**局域網**
	- MSG_OOB: 發送**帶外數據**

##### return value
- \>=0: success
- -1: failure
- errno: wrong code

### 3. writev()
- 寫多個非連續緩衝區, 稱為**聚集寫**

### 4. sendmsg()
- 類似於send, 但功能更強大

