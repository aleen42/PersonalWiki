## Unix Socket(Unix域套接字) [Back](./../IPC.md)
- Unix域Socket不是真正的網絡協議
- 既提供分佈式進程間通信, 也提供同一台機器的進程間通信
- **雙向**通道
- 分類(與pipe類似)
	- named
	- unnamed

### 1. Named Unix Socket
- Unix域協議地址
- bind時綁定一個Unix Socket時, 在該路徑名創建一個文件
- 服務器可以接受多個客戶端鏈接請求
- 使用```connect()```鏈接服務器

```c
struct socketaddr_un
{
	short int sun_family;	//AF_UNIX
	char sun_path[104];	//file path
}
```

### 2. Unnamed Unix Socket
- **socketpair**通常使用於父子進程間通信
- 父進程f[0]關閉
- 子進程f[1]關閉
- 通信前不需要進行鏈接
- socket是**全雙工**的

<img src="./socketpair.png" width="40%">

#####method
```c
int socketpair(int family, int type, int protocol, int fd[2])
```

#####parameters
- family: 必須是AF_UNIX
- type: SOCK_STREAM/SOCK_DGRAM
- protocol: 0
- fd: 存儲已創建的socket

#####return value
- 0: success
- -1: failure

