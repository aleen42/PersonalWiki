## Poll [Back](./../Coding.md)

- ```poll()```与```select()```實現的功能相似, 能監聽多個文件描述符. ```poll()```能監聽特定的某個文件描述符其返回事件
- ```poll()```比```select()```更具有細緻的分類
- ```poll()```效率要比```select()```高

##### method

```c
/* select */
unsigned int poll(struct pollfd* __fds, nfds_t __nfds, int __timeout)

/* pollfd */
struct pollfd
{
	int fd;
	short int events;	//expected events 	
	short int revents;	//return events
}
```

##### parameters
- pollfd: 設置監聽的文件描述符和期待的事件
- nfds: 文件描述符的個數
- timeout: 指定測試時間閾值上界
	- NULL: forever
	- \>0: time
	- 0: return immediately after check, without waiting

##### return value
- num: the number of ready descriptors
- 0: timeout but none is ready
- -1: failure
- errno: wrong code
