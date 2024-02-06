## UDP Socket Coding [Back](./../socket.md)
- UDP
	- does not ensure for the arrival of datagrams
		- solved by **overtime** or **Resend**
		- solved by **Serial Number** of datagrams
	- does not ensure for the order of datagrams
	- does not have **Flow Control**  
		- solved by Programming
- **Proerties** of connected UDP
	- clients should call ```connect()```, but there is not the process of three-way handshaking. ```connect()``` is used to mark down **IP** and
 **port**
	- do not need to set the address of the server when sending datagram
	- can only receive datagrams from the specifical server.
- **Server** of UDP:
	- do not accept, but bind to the port
	- **loop** for handling datagrams from different clients.
- **Client** of UDP:
	- do not connect, but choose a port when firstly calls ```sendto()```
	- can receive any datagram from any host
	- will probably be blocked forever
- **Model** of UDP Socket Coding

<img src="./udp_model.png">

### 1. recvfrom()
- recvfrom get one datagram from buffer each time, and will be blocked when there is no datagram
- **empty datagram** does not mean that the opposite end has stopped to send

##### method
```c
int recvfrom(int sockfd, void* buf, int len, unsigned char flags, struct socketaddr* from, socklen_t* addrlen)
```

##### parameters
- 前四個參數與```recv()```相同
- from: 發送者socket地址, NULL表示不需要
- addrlen: socket地址長度, from為NULL時必須設置為NULL 

##### return value
- \>=0: success
- -1: failure

### 2. sendto()
- the socket address of receiver must be clear when calling ```sendto()```
- there is no sending buffer for UDP 
- allow to send empty datagram, and return **0** after calling ```sendto()```

##### method
```c
int sendto(int sockfd, const void* buf, int len, unsigned char flags, struct socketaddr* to, int tolen)
```

##### parameters
- 前四個參數與```send()```相同
- to: 接收者socket地址
- tolen: socket地址長度

##### return value
- \>=0: success
- -1: failure

