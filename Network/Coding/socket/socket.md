## Socket [Back](./../Coding.md)

- **socket** represents the end of a channel, which is used to communicate. Thus, each end like the server or a client should have its own socket
- supports different protocols
	- UNIX
	- INET
	- IPX

#### 1.1 Create a socket
##### method
```c
int socket(int family, int type, int protocol)
```
##### parameters
- family: 協議簇
	- AF_INET
	- AF_UNIX
- type: 服務類型
	- SOCK_STREAM
	- SOCK_DGRAM
	- SOCK_RAW
- protocol: 0(default)

##### return value
- \>0: socket descriptor
- -1: failure
- errno: wrong code 

#### 1.2 Socket address
##### data structure
```c
/* common format */
struct sockaddr
{
	/* types of addr, usually AF_XXX */
	u_short sa_family;
	/* addr */
	char sa_data[14];
}

/* TCP/IP */
struct sockaddr_in
{
	short sin_family;	// AF_INET 
	u_short sin_port;	//port number
	struct in_addr sin_addr;	//IP addr
	char sin_zero[8];	//pending byte
}

struct in_addr
{
	union
	{
		struct{ u_char s_b1, s_b2, s_b3, s_b4;} S_un_b;
		struct{ u_short s_w1,s_w2;} S_un_w;
		u_long S_addr;
	}S_un;
}
```

##### method to convert addr between string and network format

```c
struct sockaddr_in addr;
/* convert string to network format */
inet_aton("219.245.78.159", &addr.sin_addr);
/* convert network format to string */
cout << inet_ntoa(addr.sin_addr) << endl;
```

##### method to get socket address and port
- ```getsockname()```
- ```getpeername()```


=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
