## Connect [Back](./../Coding.md)

- connct to the server
- 对同一個socket描述符不能兩次使用connect函數.

##### method

```c
int connect(int sockfd, struct sockaddr *servaddr, int addrlen)
```

##### parameters
- sockfd: socket描述符
- servaddr: 服務器地址
- addrlen: 地址長度

##### return value
- 0: success
- -1: failure
- errno: wrong code
