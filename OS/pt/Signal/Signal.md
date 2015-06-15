## Signal [Back](./../Network.md)
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
	- SIGINT: 中斷字符(Ctrl+C)

### 1. Send a signal to other processes
#####method
```c
/* send sig */
int raise(int sig)
/* send SIGALRM after seconds */
unsigned int alarm(unsigned int seconds)
/* send SIGABORT to exit with exception */
void abort()
```


### 2. Send a signal to itself
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


<a href="#" style="left:200px;"><img src="./../../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
