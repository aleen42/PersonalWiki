#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXDATASIZE 128
#define PORT 3000
#define BACKLOG 5

int main(int argc, char** argv)
{
	int sockfd, new_fd,nbytes, sin_size;
	char buf[MAXDATASIZE];
	struct sockaddr_in srvaddr, clientaddr;
	
	//1.创建网络端点
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		printf("can;t create socket\n");
		exit(1);
	}
	//填充地址
	bzero(&srvaddr, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(PORT);
	if(inet_aton("127.0.0.1", srvaddr.sin_addr.s_addr) == -1)
	{
		printf("addr convert error\n");
		exit(1);
	}
	//2.绑定服务器地址和端口
	if(bind(sockfd, (struct sockaddr* ) &srvaddr, sizeof(sockaddr)) == -1){
		printf("bindt error\n");
		exit(1);
	}
	//3. 监听端口
	if(listen(sockfd, BACKLOG) == -1){
		printf("listen error\n");
		exit(1);
	}
	for(;;){
		//4.接受客户端连接
		sin_size = sizeof(struct sockaddr_in);
		if((new_fd = accept(sockfd, (struct sockaddr* ) &clientaddr, &sin_size)) == -1){
			printf("accept errot\n");
			continue;
		}
		//5.接收请求
		nbytes = read(new_fd, buf, MAXDATASIZE);
		buf[nbytes] = '\0';
		printf("client:%s\n", buf);
		
		//6.回送响应
		sprintf(buf, "wellcome!");
		write(new_fd, buf, strlen(buf));
		//关闭socket
		close(new_fd);
	}
	close(sockfd);
	return 0;
}