## Read [Back](./../Coding.md)

- to read data
- read method will be **blocked** when there is no data to read until one of four situations has happened:
	- there is data
	- connection is closed, return **0**
	- connection is reset, return **error**
	- received a signal of interruption, return **error** (errno = EINTR)
- use **read_all()** to receive whole data

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

=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
