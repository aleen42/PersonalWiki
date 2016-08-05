## pipe & fifo(管道) [Back](./../IPC.md)
- 讀寫規則 (從空pipe或空fifo中讀寫):
	- Read:
		- pipe或fifo已經被只寫打開: 返回**EAGAIN**錯誤
		- pipe或fifo沒有被只寫打開: 返回**0** (文件描述符)
	- Write:
		- pipe或fifo已經被只讀打開
			- 寫入數據量不大於**PIPE_BUF** (保證原子性): 有足夠空間存放則一次性全部寫入, 沒有則返回**EAGAIN**錯誤 (不能存在部分寫入)
			- 寫入數據量大於**PIPE_BUF** (不保證原子性): 有足夠空間則全部寫入, 沒有則部分寫入後立即返回
- 額外規則:
	- 當pipe或fifio最後一個關閉時, 仍在該pipe或fifo上的數據將被丟棄 

### 1. pipe (unnamed pipe)
- **單向**通信通通道
- 只適用於有**父子**關係的進程間通信
- 實現雙向傳輸必須創建兩個管道

#####method
```c
int pipe(int fd[2])
```

#####parameters
- fd: 用於通信的一對文件描述符
	- fd[0]: **讀**
	- fd[1]: **寫**
	<img src="./pipe.png">

#####return value
- 0: success
- -1: failure

### 2. fifo (named pipe)
- 與**路徑名**相關聯, 以文件存在於文件系統
- 文件名只是便於引用, 但所對應的文件沒有數據(只適用於阻塞使用)
- 適用於任何進程間通信

#####method
```c
int mkfifo(char* pathname, mode_t mode)
```

#####parameters
- pathname: 管道名稱(絕對路徑名)
- mode: 打開文件的方式

#####return value
- 0: success
- -1: failure


