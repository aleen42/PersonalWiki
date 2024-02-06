## Read [Back](./../Coding.md)

- to read data
- read method will be **blocked** when there is no data to read until one of four situations has happened:
	- there is data
	- connection is closed, return **0**
	- connection is reset, return **error**
	- received a signal of interruption, return **error** (errno = EINTR)
- use **read_all()** to receive whole data

### 1. read()
##### method

```c
/* read method */
int read(int fd, char* buf, int len)

/* read_all method */
int read_all(int fd, void* buf, int n)
{	
	int nleft = n, nbytes;	
	char* ptr = buf;	
	for(; nleft > 0; )
	{
		nbytes = read(fd, ptr, nleft);		
		if(nbytes < 0)
		{
			if (errno == EINTR) 
				nbytes = 0;
			else 
				return -1;
		}		
		else if (nbytes == 0)
			break;		
		nleft -= nbytes;		
		ptr += nbytes;	
	}	
	return (n - nleft);
}



```

##### parameters
- fd: socket描述符
- buf: 接受緩衝區
- len: 要讀取數據的大小

##### return value
- \>=0: success
	- **len**: data of buffer is greater than len
	- **actual_len**: data of buffer is less than len
- -1: failure
- errno: wrong code

### 2. recv()
##### method

```c
int recv(int sockfd, void buf, int len, int flags)
```

##### parameters
- fd: socket描述符
- buf: 接受緩衝區
- len: 接受數據長度
- flags: 接受數據的控制參數
	- 0: read()
	- MSG_OOB: 發送**帶外數據**
	- MSG_PEEK: 接收數據後, 不從緩衝區移走數據
	- MSG_WAITALL: 數據量不夠時, 讀操作等待, 並不返回; 但在收到信號鏈接端口時, 仍然會結束

##### return value
- \>=0: success
- -1: failure
- errno: wrong code

### 3. readv()
- 讀多個非連續緩衝區, 稱為**散佈讀**

### 4. recvmsg()
- 類似recv(), 但功能更強大
