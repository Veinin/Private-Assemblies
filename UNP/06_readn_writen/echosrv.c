/**
 * process per connection
 * 一个链接一个进程处理并发，服务器的父进程负责监听，接受客户端连接; 子进程负责处理客户端的通信。
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)

void do_service(int connfd)
{
	char recvbuf[1024];
	while(1)
	{
		memset(&recvbuf, 0, sizeof(recvbuf));
		int ret = read(connfd, recvbuf, sizeof(recvbuf));
		if(ret == 0)
		{
			printf("client close\n");
			close(connfd);
			break;
		}
		else if(ret == -1)
			ERR_EXIT("read");
		printf("receve from cliend message : %s", recvbuf);
		write(connfd, recvbuf, ret);
	}
}

int main(void)
{
	int listenfd;
	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ERR_EXIT("socket");

	struct sockaddr_in srvaddr;
	memset(&srvaddr, 0, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(8888);
	srvaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int on = 1;
	if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
		ERR_EXIT("setsockopt");

	if(bind(listenfd, (struct sockaddr*)&srvaddr, sizeof(srvaddr)) < 0)
		ERR_EXIT("bind");

	if(listen(listenfd, SOMAXCONN) < 0)
		ERR_EXIT("listen");

	struct sockaddr_in cliaddr;
	socklen_t cliaddrlen = sizeof(cliaddr);
	int connfd;
	
	pid_t pid;
	while(1)
	{
		if((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddrlen)) < 0)
			ERR_EXIT("accept");

		printf("new client ip : %s, port : %d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

		pid = fork();
		if(pid < 0)
			ERR_EXIT("fork");
		else if(pid == 0) 
		{
			close(listenfd);
			do_service(connfd);
			exit(EXIT_SUCCESS);
		} else 
			close(connfd);

	}

	close(listenfd);

	return 0;
}
