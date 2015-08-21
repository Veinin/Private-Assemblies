/**
 * getsockname - 获取本地连接IP信息 
 */
#include "../unp.h"

#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int
main(void)
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

	//getsockname函数获取绑定地址
	struct sockaddr_in localaddr;
	socklen_t addrlen = sizeof(localaddr);
	if(getsockname(sockfd,(struct sockaddr*)&localaddr, &addrlen) < 0)
		ERR_EXIT("getsockname");
	printf("ip : %s, port : %d\n", inet_ntoa(localaddr.sin_addr), ntohs(localaddr.sin_port));

	char sendbuf[1024] = {0};
	char recvbuf[1024] = {0};
	while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL) 
	{
		//发送
		writen(sockfd, sendbuf, strlen(sendbuf));
	
		//接收包头部
		int ret = readline(sockfd, recvbuf, sizeof(recvbuf));
		if (ret == -1)
			ERR_EXIT("readline");
		else if(ret == 0)
		{
			printf("server close\n");
			break;
		}

		printf("server : %s", recvbuf);
		memset(&sendbuf, 0, sizeof(sendbuf));
		memset(&recvbuf, 0, sizeof(recvbuf));
	}

	close(sockfd);
	
	return 0;
}
