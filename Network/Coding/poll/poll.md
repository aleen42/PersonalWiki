## Poll [Back](./../Coding.md)

- poll比select更具有細緻的分類
- poll效率要比select高

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

<a href="#" style="left:200px;"><img src="./../../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
