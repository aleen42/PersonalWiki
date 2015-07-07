## Shared Memory & Memory Mapped File(共享內存 & 內存映射文件) [Back](./../IPC.md)
- 內存映射文件機制: 不同進程通過映射同一個普通文件實現共享內存, 進程可讀寫內存.
- 內存映射文件機制是共享內存的方式之一
- 最高效的IPC機制之一

## Shared Memory


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

### 4. Control a message queue

#####method
```c
int msgctl(int msqid, int cmd, struct msqid_ds* buf)

/* msqid_ds */
struct msqid_ds
{
	struct ipc_perm msg_perm; 
	struct msg *msg_first; /* first message on queue,unused */
	struct msg *msg_last; /* last message in queue,unused */
	__kernel_time_t msg_stime; /* last msgsnd time */ 
	__kernel_time_t msg_rtime; /* last msgrcv time */ 
	__kernel_time_t msg_ctime; /* last change time */ 
	unsigned long msg_lcbytes; /* Reuse junk fields for 32 bit */ 
	unsigned long msg_lqbytes; /* ditto */ 
	unsigned short msg_cbytes; /* current number of bytes on queue */
	unsigned short msg_qnum; /* number of messages in queue */
	unsigned short msg_qbytes; /* max number of bytes on queue */
	__kernel_ipc_pid_t msg_lspid; /* pid of last msgsnd */
	__kernel_ipc_pid_t msg_lrpid; /* last receive pid */
}

/* ipc_perm */
struct ipc_perm 
{ 
	key_t key; 
	ushort uid; /* owner euid and egid */ 
	ushort gid; 
	ushort cuid; /* creator euid and egid */ 
	ushort cgid; 
	ushort mode; /* access */ 
	ushort seq; /* slot usage sequence number */ 
};

```

#####parameters
- msqid: 消息隊列描述字
- cmd: 命令標誌
	- IPC_STAT: 獲取消息隊列信息, 返回的信息存儲在buf指向的msqid_ds結構體中
	- IPC_SET: 設置消息隊列屬性, 要設計的屬性存儲在buf指向的msqid_ds結構體中
		- msg_perm.uid
		- msg_perm.gid
		- msg_perm.mode
		- msg_qbytes
		- 影響msg_ctime成員
	- IPC_RMID: 刪除msqid標識的消息隊列		

#####return value
- 0: success
- -1: failure


<a href="#" style="left:200px;"><img src="./../../../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../../pic/tail.gif"></a>
