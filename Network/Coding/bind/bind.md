## Bind [Back](./../Coding.md)

####3.1 Bind method
- bind the local address and the port with sockfd

##### method

```c
int bind(int sockfd, struct sockaddr* myaddr, int addrlen)
```

##### parameters
- sockfd: socket描述符
- myaddr: 本機地址
- addrlen: 地址長度

##### return value
- 0: success
- -1: failure
- errno: wrong code

####3.2 INADDR_ANY
- 可以綁定任何網絡設備接口, 適用於多IP主機
- 適用於IP地址經常變化的情況

```c
struct sockaddr_in srvaddr;
srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
```

####3.3 Some problems 
- 客戶端綁定地址可能出現的問題
	- 服務器主動關閉, 導致鏈接錯誤(被關閉鏈接處於TIME_WAIT狀態)
	- 客戶端主動關閉, 導致綁定錯誤(被關閉鏈接處於TIME_WAIT狀態)
