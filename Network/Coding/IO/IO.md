## IO [Back](./../Coding.md)

- to control **IO** (input/output)

##### method

```c
int ioctl(int fd, int req, ...)
```

##### parameters
- fd: socket描述符
- req: 執行的操作類型
	- SIOCATMARK: 參數int*, 是否帶有帶外標誌
	- FIOASYNC: 參數int*, 異步標誌
	- FIONREAD: 參數int*, 緩衝區可讀數據長度
	- FIONBIO: 參數int*, 設置socket狀態(阻塞/非阻塞)
	
	```c
int on = 1;	//non-blocked mode
ioctl(sockfd, FIONBIO, &on);
	```

##### return value
- 0: success
- -1: failure
