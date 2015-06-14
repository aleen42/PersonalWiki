## Write [Back](./../Coding.md)

- to send data
- write method will be **blocked** buffer is too smaller to send data of len, until one of three situations has happened:
	- buffer is enough
	- connection is reset, return **error**
	- received a signal of interruption, return **error** (errno = EINTR)

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

=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
