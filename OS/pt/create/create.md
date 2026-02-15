## Create Processes	[Back](./../pt.md)
- 共享**代碼段**, 複製**數據段**和**堆栈段**

### 1. Create

```c
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	pid_t child_pid = fork();
	if(child_pid > 0)	
	{
		//父進程
	}
	else if(child_pid == 0)
	{
		//子進程
	}
	else
	{
		//調用失敗
	}
	return 0;
}
```

##### method

```c
pid_t fork()
```

##### return value
- \>0: 子進程的進程號, 只在父進程中返回
- -1: failure
- 0: 只在子進程返回

### 2. Execute
- ```execl()```調用後, 當前進程"死亡", 代碼段替換, 然後創建新的數據段及堆棧段, 保留原有的進程號.

##### method
```c
int execve(const char* path, char* const argv[], char* envp)
int execl(const char* path, const char* argv, ...)
```

##### parameters
- path: 程序路徑名
- argv: 命令行參數

##### return value

