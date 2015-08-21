/**
 * 点对点聊天程序 - 服务器端
 */
#include "../unp.h"

#include <stdio.h>
#include <string.h>

#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void handler(int signo)
{
	printf("recv a signo = %d\n", signo);
	exit(EXIT_SUCCESS);
}

int main(void) 
{
	int listenfd;
	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ERR_EXIT("socket");

	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8888);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
		ERR_EXIT("bind");

	if(listen(listenfd, SOMAXCONN) < 0)
		ERR_EXIT("listen");

	int connfd;
	struct sockaddr_in cliaddr;
	socklen_t cliaddrlen = sizeof(cliaddr);
	if((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddrlen)) < 0)
		ERR_EXIT("accept");
	else
		printf("ip : %s, port : %d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

	pid_t pid;
	pid = fork();
	if(pid == -1)
		ERR_EXIT("fork");

	if(pid == 0) //子进程发送消息
	{
		signal(SIGUSR1, handler);
		char sendbuf[1024] = {0};
		while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
		{
			write(connfd, sendbuf, strlen(sendbuf));
			memset(sendbuf, 0, sizeof(sendbuf));
		}
		printf("child close\n");
		exit(EXIT_SUCCESS);
	}
	else	//父进程接受消息
	{
		char readbuf[1024];
		while(1)
		{
			memset(readbuf, 0, sizeof(readbuf));
			int ret = read(connfd, readbuf, sizeof(readbuf));
			if(ret < 0)
				ERR_EXIT("read");
			else if(ret == 0) 
			{
				printf("peer close\n");
				break;
			}

			fputs(readbuf, stdout);
		}
		printf("parent close\n");
		kill(pid, SIGUSR1);
		exit(EXIT_SUCCESS);
	}

	return 0;
}
