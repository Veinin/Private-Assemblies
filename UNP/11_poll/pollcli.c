/*
 * select - client
 */
#include "../unp.h"

void
echo_cli(int sockfd)
{
	int nready;

	struct pollfd pollfds[2];
	
	pollfds[0].fd = sockfd;
	pollfds[0].events = POLLIN;

	pollfds[1].fd = fileno(stdin);
	pollfds[1].events = POLLOUT;

	char sendbuf[1024] = {0};
	char recvbuf[1024] = {0};

	while (1)
	{
		nready = poll(pollfds, 2, -1);
		if (nready == -1)
			ERR_EXIT("select");

		if (nready == 0)
			continue;

		if (pollfds[0].revents & POLLIN)
		{
			int ret = readline(sockfd, recvbuf, sizeof(recvbuf));
			if (ret == -1)
				ERR_EXIT("readline");
			else if(ret == 0)
			{
				printf("server close\n");
				break;
			}

			printf("server : %s", recvbuf);
			memset(recvbuf, 0, sizeof(recvbuf));
		}

		if (pollfds[1].revents & POLLOUT)
		{
			if (fgets(sendbuf, sizeof(sendbuf), stdin) == NULL)
				break;

			writen(sockfd, sendbuf, strlen(sendbuf));
			memset(sendbuf, 0, sizeof(sendbuf));
		}
	}
	
	close(sockfd);
}

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

	echo_cli(sockfd);
	
	return 0;
}
