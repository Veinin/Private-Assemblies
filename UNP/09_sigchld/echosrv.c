/**
 * 僵死进程
 * 客户端关闭，子进程关闭时，父进程未对子进程发送的SIGCHILD信号进行处理，导致子进程一直处于等待父进程为其收尸状态
 * 这个状态下的子进程就是僵死进程
 */
#include "../unp.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void
handler_sigchild(int signo)
{
	while (waitpid(-1, NULL, WNOHANG) > 0) //等待所有子进程关闭
		;
}

void
echo_srv(int connfd)
{
	char recvbuf[1024];
	while(1)
	{
		memset(&recvbuf, 0, sizeof(recvbuf));
		//接收消息
		int ret = readline(connfd, recvbuf, sizeof(recvbuf));
		if (ret == -1)
			ERR_EXIT("readline");
		else if (ret == 0)
		{
			printf("server close\n");
			break;
		}
		
		printf("client : %s", recvbuf);
		//回射给客户端
		writen(connfd, recvbuf, strlen(recvbuf));
	}
}

int
main(void)
{
	//客户端关闭后，僵死子进程处理
	signal(SIGCHLD, handler_sigchild);	

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

		printf("ip : %s, port : %d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

		pid = fork();
		if(pid < 0)
			ERR_EXIT("fork");
		else if(pid == 0) 
		{
			close(listenfd);
			echo_srv(connfd);
			exit(EXIT_SUCCESS);
		} else 
			close(connfd);

	}

	close(listenfd);

	return 0;
}
