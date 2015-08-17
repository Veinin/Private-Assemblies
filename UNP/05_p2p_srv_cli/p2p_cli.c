/**
 * 点对点聊天程序 - 客户端
 */
#include <stdio.h>
#include <error.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

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

void handler(int signo)
{
	printf("recv a signo = %d\n", signo);
	exit(EXIT_SUCCESS);
}

int main(void)
{
	int sockfd;
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ERR_EXIT("socket");

	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8888);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
		ERR_EXIT("connect");

	pid_t pid;
	pid = fork();
	if(pid == -1)
		ERR_EXIT("fork");

	if(pid == 0) //子进程接受消息
	{
		char recvbuf[1024];
		while(1)
		{
			memset(recvbuf, 0, sizeof(recvbuf));
			int ret = read(sockfd, recvbuf, sizeof(recvbuf));
			if(ret < 0)
				ERR_EXIT("read");
			else if(ret == 0)
			{
				printf("peer cloase\n");
				break;
			}

			fputs(recvbuf, stdout);
		}
		
		printf("child close\n");
		kill(getppid(), SIGUSR1);
		close(sockfd);
	}
	else         //父进程发送消息
	{
		signal(SIGUSR1, handler);
		char sendbuf[1024] = {0};
		while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
		{
			write(sockfd, sendbuf, strlen(sendbuf));
			memset(sendbuf, 0, sizeof(sendbuf));
		}

		printf("parent close\n");
		close(sockfd);
	}

	return 0;
}
