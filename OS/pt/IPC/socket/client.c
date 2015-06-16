//-------------client.c-----------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <unistd.h>
#include <termios.h>
#include <sys/stat.h>

//----------headfile of timer--------
#include <sys/time.h>
#include <signal.h>

//--------headfile of SOCKET commnication-------
#include <sys/socket.h>
#include <sys/un.h>

#include <sys/ioctl.h>
#pragma pack(1)			//set align of 1 byte
#define UNIX_DOMAIN "/tmp/UNIX2.domain"
static char send_php_buf[256] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };
/*struct test
{
	char a;
	int b;
	int c;
}se;*/

int main(int argc, char** argv)
{
	int connect_fd;
	int ret = 0;
	int i;
	static struct sockaddr_un srv_addr;
	printf("IPC Communication Thread\n");

	//while (1)
	//{
		//create a socket for communication,and domain is UNIX domain
		connect_fd = socket(AF_UNIX, SOCK_STREAM, 0);
		printf("%d\n", connect_fd);
		if (connect_fd < 0)
		{
			perror("cannot create communication socket");
			printf("%d\n", connect_fd);
			return -1;

		}
		else
		{
			srv_addr.sun_family = AF_UNIX;
			strcpy(srv_addr.sun_path, UNIX_DOMAIN);

			//Connect to the server
			//int connect(int socket,const struct sockaddr* address,size_t address_len)		success:return 0	fault:return -1
			ret = connect(connect_fd, (struct sockaddr*)&srv_addr, sizeof(srv_addr));
			if (ret == -1)
			{
				close(connect_fd);
				printf("connect fail\n");
				//break							//create socket again
				close(connect_fd);
				return -1;
			}
			else
			{
				//successful to connect to the server
				/*se.a = 0x01;
				se.b = 0x01020304;
				se.c = 0x05060708;*/
				write(connect_fd, send_php_buf, 20);			//send data to the exteral application,send the real length
				//write(connect_fd,&se,sizeof(struct test));
				memset(send_php_buf, 0, sizeof(send_php_buf));	//clear the socket_buf
				//sleep(1);
				//fcnt(connect_fd,F_SETEL,O_NONBLOCK);
				read(connect_fd, send_php_buf, sizeof(send_php_buf));
				
				printf("receive from server over\n");
				for (i = 0; i < 20; i++)
				{
					printf("%x", send_php_buf[i]);
				}
				//printf("%x",se.c);
				printf("\n");
				close(connect_fd);


			}
		}
	//}
	return 0;
}
