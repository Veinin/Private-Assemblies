/*
 * select - client
 */
#include "../unp.h"

int
main(void)
{
	int count = 0;
	while (1)
	{
		int sockfd;
		if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			sleep(10); //延迟关闭sockfd，测试并发数量
			ERR_EXIT("socket");
		}

		struct sockaddr_in servaddr;
		memset(&servaddr, 0, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(8888);
		servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

		if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) 
			ERR_EXIT("connect");
		
		struct sockaddr_in localaddr;
		socklen_t localaddrlen = sizeof(localaddr);
		if (getsockname(sockfd, (struct sockaddr*) &localaddr, &localaddrlen) < 0)
			ERR_EXIT("getsockname");

		printf("ip=%s port=%d\n", inet_ntoa(localaddr.sin_addr), ntohs(localaddr.sin_port));
		printf("count = %d\n", count++);
	}
	
	return 0;
}
