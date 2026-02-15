## Semaphore(信號量) [Back](./../IPC.md)

- 信號量主要提供對進程間共享資源訪問的控制機制.
- 可用於**訪問控制**和**進程間同步**
- 類型:
	- **二值信號量**: Boolean類型
	- **計數信號量**: 非負值

### 0. Header Files

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
```

### 1. Create

- 调用成功時, 初始化相應的控制塊信息

#####method
```c
int semget(key_t key, int nsems, int flags)
```

#####parameters
- key: 鍵值, 由```ftok()```獲取
	- IPC_PRIVATE: key由系統分配
- nsems: 信號量數
- flags: 操作標誌, 決定了信號量組的創建方式和權限

#####return value
- >0: 信號量組標識符
- -1: failure

### 2. Operation

#####method
```c
int semop(int sid, struct sembuf** ops, unsigned nops)

/* sembuf */
struct sembuf
{
	short sem_num;  /* 信号量编号，從0開始 */
	short sem_op;   	/* 要執行的操作 */
	short sem_flg;  	/* 操作標誌 */
};

```

#####parameters
- sid: ```semget()```返回的信號量組標識符
- ops: 操作的數據結構
- nops: 操作的個數


#####return value
- 0: success
- -1: failure

### 3. Control

#####method
```c
int semctl(int sid, int snum, int cmd, union semun arg)

/* semun */
union semun
{
	int val;
	struct semid_ds* buf;	/* 指針信號量組控制塊的指針 */
	ushort* array;
};
```

#####parameters
- sid: ```semget()```返回的信號量組標識符
- snum: 信號燈編號
- cmd: 命令

#####return value
- >0: success(與cmd相關)
- -1: failure


