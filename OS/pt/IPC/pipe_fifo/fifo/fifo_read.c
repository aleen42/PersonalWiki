//--------fifo_read.c-----------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define FIFO_FILE "/tmp/myfifo"

int main()
{
	char buf[100];
	int n = 0;
	int fd;
	//匿名管道(unnamed pipe)：只能用于同一个祖先的进程组通信 
	//有名管道(named fifo)：不相关的进程也可以使用来通信 
	//unnamed pipe:int pipe(int filedes[2]); 	fildes[0]:用于从管道中读取数据;	fildes[1]:用于将数据写入管道(不需要open，直接read/write,等系统调用，系统自动删除，进程不需要考虑。)
	//named pipe: int mkfifo(const char* pathname, mode_t mode);
	
	
	if ((mkfifo(FIFO_FILE, S_IRWXU) < 0) && (errno != EEXIST))	//empty exist	//if fifo does not exist, then create it
	{
		perror("mkfifo error");
		exit(-1);
	}
	
	if ((fd = open(FIFO_FILE, O_RDONLY | O_NONBLOCK)) < 0)		//open fifo in a unblock way
	{
		perror("open error");
		exit(-1);
	}
	
	while (1)
	{
		if ((n = read(fd, buf, 100)) < 0)	//FIFO_FILE has been opened.	
		{
			if (errno == EAGAIN)		//empty gain
			{
				printf("No data yet\n");
			}
		}
		else if (n == 0)					//FIFO_FILE is not opened yet
			printf("No opened by write_only\n");
		else
			write(STDOUT_FILENO, buf, n);	//equal to printf("%s",buf);
		sleep(1);
	}
	unlink(FIFO_FILE);
	return 0;
}
