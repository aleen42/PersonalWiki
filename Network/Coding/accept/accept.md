## Accept [Back](./../Coding.md)

- accept the connection of clients
- new socket descriptor is different from the old one
	- **The old socket descriptor** is to listen to the connections of clients. 
	- **The new socket descriptor** is to handle communications between the server and the client.
- accept method will be **blocked** until complete a connection

##### method

```c
int accept(int sockfd, struct sockaddr* clientaddr, int* addrlen)
```

##### parameters
- sockfd: socket描述符
- clientaddr: 客戶端地址
- addrlen: 地址長度

##### return value
- \>0: new socket descriptor
- -1: failure
- errno: wrong code
