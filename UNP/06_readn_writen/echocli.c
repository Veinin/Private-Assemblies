/**
 * readn - writen - client 
 */
#include "../unp.h"

#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

struct packet
{
	int len;	//包头
	char buf[1024]; //包缓冲区
};

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

	struct packet sendbuf;
	struct packet recvbuf;
	memset(&sendbuf, 0, sizeof(sendbuf));
	memset(&recvbuf, 0, sizeof(recvbuf));
	int n;
	while(fgets(sendbuf.buf, sizeof(sendbuf.buf), stdin) != NULL) 
	{
		//发送
		n = strlen(sendbuf.buf);
		sendbuf.len = htonl(n);
		writen(sockfd, &sendbuf, 4 + n);
	
		//接收包头部
		int ret = readn(sockfd, &recvbuf.len, 4); if(ret == -1)
			ERR_EXIT("read");
		else if(ret == 0)
		{
			printf("server close\n");
			break;
		}

		//接受包内容
		n = ntohl(recvbuf.len);
		ret = readn(sockfd, &recvbuf.buf, n);
		if(ret == -1)
			ERR_EXIT("read");
		else if(ret == 0)
		{
			printf("client close\n");
			break;
		}

		printf("receive message : %s", recvbuf.buf);
		memset(&sendbuf, 0, sizeof(sendbuf));
		memset(&recvbuf, 0, sizeof(recvbuf));
	}

	close(sockfd);
	
	return 0;
}
