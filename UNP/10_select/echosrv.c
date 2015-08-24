/**
 * select - server
 */
#include "../unp.h"

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
	int listenfd;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ERR_EXIT("socket");

	struct sockaddr_in servaddr;

	if ((

	return 0;
}
