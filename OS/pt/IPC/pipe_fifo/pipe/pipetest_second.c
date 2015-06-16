//---------pipetest_second.c----------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char** argv)
{
	int pipe_fd[2];
	pid_t pid;
	char r_buf[4];
	char* w_buf;
	int writenum;
	int cmd;

	memset(r_buf, 0, sizeof(r_buf));
	
	if (pipe(pipe_fd) < 0)
	{
		printf("pipe create error\n");
		return -1;
	}

	if (pid = fork() == 0)				//child process
	{
		close(pipe_fd[0]);				//close reader
		close(pipe_fd[1]);				//close writer
		sleep(10);						//ensure that two have been closed
		exit(0);
	}
	else if (pid > 0)					//parent process
	{
		sleep(1);						//wait for the closing of child process
		close(pipe_fd[0]);				//close writer
		w_buf = "13121215";
		printf("FILE: %s,LINE: %d\r\n", __FILE__, __LINE__);
		if ((writenum = write(pipe_fd[1], w_buf, sizeof(w_buf))) == -1)
			printf("write to pipe error\n");
		else
			printf("the bytes writ to pipe is %d\n", writenum);

		printf("FILE: %s,LINE: %d\r\n", __FILE__, __LINE__);
		close(pipe_fd[1]);
	}
}
