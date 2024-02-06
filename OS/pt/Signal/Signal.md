## Signal [Back](./../pt.md)
- Linux中信號是對中斷的軟件模擬
- 進程收到信號, 如同CPU收到了中斷請求
- 信號是**異步**的
- 信號來源:
	- 硬件: 鍵盤輸入或硬件錯誤
	- 軟件: 其他進程或內核
- 信號分類:
	- SIGALARM: 計時器到時信號
	- SIGCHLD: 子進程停止或退出通知父進程的信號
	- SIGKILL: 終止進程信號
	- SIGSTOP: 停止進程信號
	- SIGINT: 中斷信號(Ctrl+C)
	- SIGQUIT: 退出信號(Ctrl+Backspace)
	- SIGURG: 緊急信號(帶外數據到達)

### 1. Send a signal to itself
#####method
```c
/* send sig */
int raise(int sig)
/* send SIGALRM after seconds */
unsigned int alarm(unsigned int seconds)
/* send SIGABORT to exit with exception */
void abort()
```


### 2. Send a signal to other processes
#####method
```c
int kill(pid_t pid, int sig)
```

#####parameters
- pid: 接受信號的進程集合
	- \>0: 進程號為pid的進程
	- 0: 同一個進程組的進程
	- -1: 進程號為-pid的進程
	- <-1: 除進程自身外所有進程號大於1的進程
- sig: 要發送的信號

### 3. Handle a signal with ```sigaction()```
#####method
```c
int sigaction(int signum, const struct sigaction* act, struct sigaction* oldact)

struct sigaction
{
	void(*sa_handler)(int);
	void(*sa_sigaction)(int, siginfo_t*, void*);
	sigset_t sa_mask;	屏蔽的信號集
	int sa_flags;	//標誌
	void(*sa_restorer)(void);		//已廢棄
}
```

#####parameters
- signum: 指定需要捕獲的信號(SIGKILL, SIGSTOP不能指定)
- act: 指定處理所捕獲信號的新動作
- oldact: 存儲舊的動作
- sa_handler/sa_sigaction: 信號處理函數(sa_flags=SA_SIGINFO時, sa_sigaction有效)
	- SIG_DFL: 默認動作
	- SIG_IGN: 忽略信號
	- 用戶指定处理函数
- sa_mask: 指定信號處理函數中屏蔽的信號集, 通常被處理的信號本身被屏蔽
- sa_flags: 影響信號處理函數行為的標誌
	- SA_ONESHOT/SA_RESETHAND: 信號處理後, 設置為默認動作
	- SA_RESTART: 某些系統調用在被信號中斷自動重新執行
	- SA_NOCLDSTOP: 當signum=SIGCHLD時, 子進程停止不通知父進程
	- SA_NOMASK或SA_NODEFER: 該信號不被屏蔽

### 4. Handle a signal with ```signal()```
#####method
```c
sighandler_t signal(int signum, sighandler_t handler)
/* sighandler_t */
typedef void(*sighandler_t)(int) sighandler_t;
```

#####parameters
- signum: 指定需要捕獲的信號(SIGKILL, SIGSTOP不能指定)
- handler: 指定信號處理函數

#####return value
- 原來的信號處理函數

### 5. Operations with sets of signals
- ```int sigemptyset(sigset_t* set)```清空信號集
- ```int sigfillset(sigset_t* set)```將所有信號加入信號集
- ```int sigaddset(sigset_t* set, int signum)```添加信號到信號集
- ```int sigismember(const sigset_t* set, int signum)```檢測一個信號是否存在於信號集中

### 6. Signal Jam & Signal Omit
- Signal Mask/Jam(信號屏蔽/阻塞): 信號被阻塞到進程外, 等到阻塞解除才能進入
- Signal Omit(信號忽略): 信號被進程忽略並丟棄

### 7. Change current mask set

#####method
```c
int sigprocmask(int how, sigset_t* set, sigset_t* oldset)
```

#####parameters
- how: 決定如何改變當前被屏蔽(阻塞)的信號集
	- SIG_BLOCK: 取當前屏蔽信號集和set的並集
	- SIG_UNLOCK: 取當前屏蔽信號集和set的差集
	- SIG_SETMASK: 用set替換當前屏蔽信號集
- set: 指定的信號集
- oldset: 存儲舊的信號集

### 8. Check current mask set

- ```sigsuspend()```可用於實現進程同步

#####method
```c
int sigpending(sigset_t* set)
sigsuspend(const sigset_t* mask)
```

#####parameters
- set: 指定的信號集
- mask: 臨時用mask替換當前進程的信號掩碼, 並暫停進程執行直到收到信號


