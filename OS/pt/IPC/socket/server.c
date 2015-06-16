//-------------server.c-----------
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

#define UNIX_DOMAIN "/tmp/UNIX2.domain"
static char recv_php_buf[256];		//receive the data from the buffer of client
static int recv_php_num = 0;		//receive the total length of the data from clent

int main(int argc, char** argv)
{
	socklen_t clt_addr_len;
	int listen_fd;					//socket file
	int com_fd;
	int ret = 0;
	int i;

	int len;
	struct sockaddr_un clt_addr;
	struct sockaddr_un srv_addr;	//server_addr				//sockaddr_un-->AF_UNIX's addr form
																struct sockaddr_un
																{
																	sa_family_t sun_family;		/*AF_UNIX*/
																	char sun_path[];			/*pathname*/
																}						
															//sockaddr_in-->AF_INET's addr form
																struct sockaddr_in
																{
																	short int sin_family;		/*AF_INET*/
																	unsigned short int sin_port;/*port number*/
																	struct in_addr sin_addr;	/*internet addr*/
																}
																
																struct in_addr
																{
																	unsigned long int s_addr;	/*ip addr*/
																}
	while (1)
	{
		//create a socket for communication, communication domain is UNIX domain
		//int socket(int domain,int type,int protocol)	success:return socket;	fault:return -1;
		listen_fd = socket(AF_UNIX, SOCK_STREAM, 0);		//AF_UNIX: Unix Domain
															//SOCK_STREAM:reliable (TCP)
															//SOCK_DGRAM:unreliable (UDP)
															//指定socket的协议类型，我们一般指定为0表示由第一第二两个参数自动选择
		if (listen_fd < 0)
		{
			perror("cannot create listening socket");
			continue;
		}
		else
		{
			while (1)
			{
				//set the addr parameter for the server
				srv_addr.sun_family = AF_UNIX;
				strncpy(srv_addr.sun_path, UNIX_DOMAIN, sizeof(srv_addr.sun_path) - 1);
				unlink(UNIX_DOMAIN);

				//bind socket with the addr information f the server
				//int bind(int socket,const struct sockaddr* address,size_t address_len)	success:return 0;	fault:return -1;
				ret = bind(listen_fd, (struct sockaddr*)&srv_addr, sizeof(srv_addr));
				if (ret == -1)
				{
					perror("cannot bind server socket");		//print error system message
					close(listen_fd);
					unlink(UNIX_DOMAIN);						//remove specificated file
					break;
				}

				//listen to the socket and adjust whether there is a connect request
				//int listen(int socket,int backlog)	backlog:the max num of connection waited by the server	success:return 0;	fault:return -1;
				ret = listen(listen_fd,1);
				if (ret == -1)
				{
					perror("cannot listen the client connect request");
					close(listen_fd);
					unlink(UNIX_DOMAIN);
					break;
				}

				chmod(UNIX_DOMAIN, 00777);	//set the priorty of communication file
				while (1)
				{
					//when there is a connect request, call accept() to set the connection between server and client
					len = sizeof(clt_addr);
					//int accept(int socket,struct sockaddr* address,size_t* address_len)	success:return socket;	fault:return -1;
					com_fd = accept(listen_fd, (struct sockaddr*)&clt_addr, &len);
					if (com_fd < 0)
					{
						perror("cannot accept client connect request");
						close(listen_fd);
						unlink(UNIX_DOMAIN);
						break;
					}

					//read and output the connect information from client
					memset(recv_php_buf, 0, 256);
					recv_php_num = read(com_fd, recv_php_buf, sizeof(recv_php_buf));			//com_fd----->recv_php_buf
					printf("\n=====recv=====\n");
					for (i = 0; i < recv_php_num; i++)
					{
						printf("%d", recv_php_buf[i]);
					}
					printf("\n");
					/*if (recv_php_buf[0] == 0x02)
					{
						if (recv_php_buf[recv_php_num - 1] == 0x00)
						{
							recv_php_buf[recv_php_num - 1] = 0x01;
						}
						else
						{
							recv_php_buf[recv_php_num - 1] = 0x00;
						}
					}*/
					//recv_php_buf[20] += 1;
					write(com_fd, recv_php_buf, recv_php_num);									//recv_php_buf---->com_fd
					printf("\n=====send=====\n");
					for (i = 0; i < recv_php_num; i++)
					{
						printf("%d", recv_php_buf[i]);
					}
					printf("\n");
					//write(com_fd, recv_php_buf, 20);
					close(com_fd);	//WARNING: remember to close the connect 
				}
			}
		}
	}
	return 0;
}
