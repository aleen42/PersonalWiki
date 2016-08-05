## Kill Processes [Back](./../pt.md)
- call ```exit()``` to kill processes
	- if the process is the group leader of a processes group, then send **SIGHUP** to all processes in this group
	- close all **socket** opened by this process
	- if there are children process, then set their parent as **init process**
	- send **SIGCHLD** to its parent
- **Zombie(僵屍) Process** will be created when SIGCHLD is not handled by its parent
	- Zombies will occupy a **Process Table Entry(進程表項)** in the system
- ways to kill Zomebie Process
	- ignore SIGCHLD using **SIG_IGN**, and system will clear their Process Table Entries.
	- use ```wait()``` or ```waitpid()``` to wait for killing child processes.
	- use ```waitpid()``` to handler more than one killing child process by setting **WNOHANG**, prevented to be blocked, rather than ```wait()```.
	- ```fork()``` twice so that child process will be controled by init process.

#####method

```c
pid_t waitpid(pid_t pid, int* status, int option)
```

#####parameters
- pid: 進程id
	- \>0: 只等待進程號為pid的子進程退出
	- -1: 等待任何子進程退出
- option: 選項
	- WHONANG: 無子進程退出時不阻塞
- status: 存儲狀態信息

#####return values
- 退出的子進程id
- 0: 設置WHONANG且無子進程退出
- -1: failure
- errno: error code

