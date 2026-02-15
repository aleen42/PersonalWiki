## Socket [Back](./../Coding.md)

- **socket** represents the end of a channel, which is used to communicate. Thus, each end like the server or a client should have its own socket
	- [**UDP Socket Coding**](./UDP/UDP.md)
	- [**Original Socket Coding**](./original/original.md)
- supports different protocols
	- UNIX
	- INET
	- IPX

### 1. Create a socket
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

### 2. Socket address
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

### 3. Socket options
##### method
```c
/* get options of sockets */
int getsockopt(int sockfd, int level, int optname, void* optval, sock_len *optlen)
/* set options of sockets */
int setsockopt(int sockfd, int level, int optname, void* optval, sock_len optlen)
/* set socket to blocked/non-blocked mode, set/get owners of the socket */
int fcntl(int fd, int cmd, ...)
```

##### parameters
- sockfd: socket描述符
- level: 選項級別
	- SOL_SOCKET: 通用socket選項
		- SO_KEEPALIVE: 2小時內若無數據交換, TCP協議將自動發送探測數據包來檢測網絡連接
		- SO_RCVBUF/SO_SNDBUF: 設置發送或接受緩衝區大小
		- SO_RCVTIMEO/SO_SNDTIMEO: 設置發送或接受函數的時間閾值上界
		- SO_REUSEADDR: 
			- 重用處於TIME_WAIT狀態, 具有相同本地地址和端口的socket; 
			- 允許同一個端口啟動同一個服務器多個實例(多個進程), 但IP不能相同; 
			- 允許單個進程綁定相同的端口到多個socket上, 但IP不能相同; 
			- 允許完全相同的地址和端口重複綁定, 只用於UDP的多播, 而不用於TCP;
	- IPPROTO_IP: IP選項
		- IP_HDRINCL: 是否自己建立IP數據包頭
	- IPPROTO_TCP: TCP選項
		- TCP_MAXSEG: TCP協議最大數據段長度
		- TCP_NODELAY: 小數據包是否延遲發送
- optname: 選項名字
- optval: 選項值
- optlen: 选项值長度(存放選項值長度的指針)

- fd: 文件(socket)描述符
- cmd: 執行的操作
	- F_GETFL: 獲得描述符標誌
	- F_SETFL: 參數O_NONBLOCK, 設置socket為非阻塞模式

	```c
/* set to non-blocked mode */
flags = fcntl(fd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(fd, F_SETFL, flags);
/* set to blocked mode */
flags = fcntl(fd, F_GETFL, 0);
flags &= ^O_NONBLOCK;
fcntl(fd, F_SETFL, flags);
	```
	- F_GETOWN: 參數int*, 獲得socket的擁有者
	- F_SETOWN: 參數int, 設置socket的擁有者

##### return value
- 0: success
- -1: failure

