## Message Queue(消息隊列) [Back](./../IPC.md)
- 消息隊列就是一個消息的鏈表.
- 消息具有特定的格式以及特定的優先級.
- 消息隊列是**隨內核持續**的.
- 與管道相比:
	- 消息隊列提供有格式字节流, 從而減少開發人員的工作量
	- 消息具有類型, 可分優先級
	- 消息隊列的生命週期更長

### 0. Header files
```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
```

### 1. Create a Message Queue
#####method
```c
int msgget(key_t key, int msgflag)
```

#####parameters
- key: 鍵值, 由```ftok()```獲取
- msgflag: 消息標誌
	- IPC_CREATE: 如果內核中不存在則創建
	- IPD_EXCEL: 若和IPC_CREATE一起使用, 若內核中存在則返回失敗

#####return value
- >0: 消息隊列描述字
- -1: failure

### 2. Receive messages

- receive method will be **blocked** when there is no data to read until one of three situations has happened:
	- there is data
	- the message queue of **msgid** was killed
	- received a signal of interruption, return **error** (errno = EINTR)

#####method
```c
int msgrcv(int msqid, struct msgbuf* msgp, int msgsz, long msgtyp, int msgflg)
```

#####parameters
- msqid: 消息隊列描述字
- msgp: 接受信息的數字結構
- msgsz: 消息長度(指定msgp中mtex成員的長度)
- msgtyp: 請求讀取的消息類型
- msgflg: 讀消息的標誌
	- IPC_NOWAIT: 若無滿足條件的消息, 調用立即返回(errno = ENOMSG)
	- IPC_EXCEPT: 返回隊列中第一個類型**不為**msgtyp的消息
	- IPC_NOERROR: 若滿足條件的消息內容大於所請求的msgsz, 則把消息截斷, 截斷部分將丟失

#####return value
- >0: 讀出消息的實際字節數
- -1: failure

### 3. Send messages

- send method will be **blocked** when there is no data to read until one of three situations has happened:
	- there is sufficient space for sending messages
	- the message queue of **msgid** was killed
	- received a signal of interruption, return **error** (errno = EINTR)

#####method
```c
int msgsnd(int msqid, struct msgbur* msgp, int msgsz, int msgflg)
```

#####parameters
- msqid: 消息隊列描述字
- msgp: 發送信息的數字結構
- msgsz: 消息長度(指定msgp中mtex成員的長度)
- msgflg: 讀消息的標誌
	- IPC_NOWAIT: 若消息隊列沒有足夠空間容納發送消息時, 調用立即返回(errno = ENOMSG)

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


