## Shared Memory & Memory Mapped File [Back](./../IPC.md)

- 共享內存機制: 進程間需要共享的數據被放在**IPC共享內存區域**, 若要訪問則把該共享區域映射到本進程的地址空間中.
- 內存映射文件機制: 不同進程通過映射同一個普通文件實現共享內存, 進程可讀寫內存.
- 內存映射文件機制是共享內存的方式之一
- 最高效的IPC機制之一

## Shared Memory

### 1. Create a shared memory area

#####method
```c
int shmget(key_t key, int nbytes, int flags)
```

#####parameters
- key: 鍵值, 由```ftok()```獲取
	- IPC_PRIVATE: key由系統分配
- flags: 標誌位
	

#####return value
- >0: 共享段的描述字id
- -1: failure

### 2. Map

- 把該共享區域映射到本進程的地址空間中.

#####method
```c
char* shmat(int segid, char* addr, int flags)
```

#####parameters
- segid: ```shmget()```返回的共享段描述字
- addr: 映射目的地的地址, 若不關心則設置為0(有系統選擇可用地址)


#####return value
- 共享內存段在進程地址空間的首地址

### 3. Unmap

- 調用成功後內存段訪問計數減一

#####method
```c
int shmdt(char* addr)
```

#####parameters
- addr: ```shmat()```返回的首地址

#####return value
- 0

### 3. Control

#####method
```c
int shmct(int segid, int cmd, struct shmid_ds* sbuf)
```

#####parameters
- segid: ```shmget()```返回的共享段描述字
- cmd: 命令
	- SHM_LOCK: 共享段鎖定在內存, 禁止換出(Root用戶才有權限)
	- SHM_UNLOCK: 與LOCK相反
	- IPC_STAT: 獲取消息隊列信息, 返回的信息存儲在sbuf指向的shmid_ds結構體中
	- IPC_SET: 設置消息隊列屬性, 要設計的屬性存儲在sbuf指向的shmid_ds結構體中
	- IPC_RMID: 存儲段可釋放

#####return value
- 0: success
- -1: failure

## Memory Mapped File

### 1. Map

#####method
```c
void* mmap(void* addr, size_t len, int prot, int flags, int fd, off_t offset)
```

#####parameters
- fd: 文件描述符, 一般由```open()```獲取
- len: 映射區的大小(從文件開頭的offset個字節後開始計算)
- prot: 指定共享內存的訪問權限
- offset: 文件頭, 一般設置為0
- addr: 指定映射的地址

#####return value
- 最終映射的地址

### 2. Unmap

#####method
```c
int munmap(void* addr, size_t len)
```

#####parameters
- addr: ```mmap()```最終映射的地址
- len: 映射區的大小

#####return value
- 0: success
- -1: failure

### 3. Data Synchronize

- 實現磁盤上文件內容與共享內存區的內容同步.
- 共享內容改變一般不會採用**寫直達法**寫回磁盤文件, 而是當```munmap()```被調用後才寫回.

#####method
```c
int msync(void* addr, size_t len, int flags)
```

#####parameters
- addr: ```mmap()```最終映射的地址
- len: 映射區的大小
- flags: 同步標誌

#####return value
- 0: success
- -1: failure


