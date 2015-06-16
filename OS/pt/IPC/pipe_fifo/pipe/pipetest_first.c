//---------pipetest_first.c----------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

int main(unsigned int argc, unsigned char** argv)
{
	int pipe_fd[2];
	pid_t pid;
	char r_buf[100];
	char w_buf[4];
	int r_num;
	int cmd;

	memset(r_buf, 0, sizeof(r_buf));
	memset(w_buf, 0, sizeof(r_buf));
	//匿名管道(unnamed pipe)：只能用于同一个祖先的进程组通信 
	//有名管道(named fifo)：不相关的进程也可以使用来通信 
	//unnamed pipe:int pipe(int filedes[2]); 	fildes[0]:用于从管道中读取数据;	fildes[1]:用于将数据写入管道(不需要open，直接read/write,等系统调用，系统自动删除，进程不需要考虑。)
	//named pipe: int mkfifo(const char* pathname, mode_t mode);
	if (pipe(pipe_fd) < 0)
	{
		printf("FILE: %s,LINE: %d.pipe create error\n", __FILE__, __LINE__);
		return -1;
	}
	if ((pid = fork()) == 0)				//child process
	{
		printf("####################\n");
		close(pipe_fd[1]);					//close writer
		sleep(3);							//ensure the writer has closed
		r_num = read(pipe_fd[0], r_buf, 100);
		printf("child read num is %d, the data read from the pipe is %d\n", r_num, atoi(r_buf));
		close(pipe_fd[0]);					//close reader
		//exit(0);
	}
	else if (pid > 0)						//parent process
	{
		close(pipe_fd[0]);					//close reader
		strcpy(w_buf, "111");
		if (write(pipe_fd[1], w_buf, 4) != -1)
		{
			printf("parent write over\n");
		}
		close(pipe_fd[1]);					//close writer
		printf("parent close fd[1]-write over\n");
		sleep(3);
	}
	return 0;
}