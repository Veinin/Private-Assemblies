#include "../unp.h"

void
echo_cli(int sockfd, struct sockaddr *servaddr, socklen_t servaddrlen)
{
	fd_set rset;

	int maxfd = sockfd;
	int stdin_fd = fileno(stdin);
	if(stdin_fd > sockfd)
		maxfd = stdin_fd;

	int nready, ret;
	char sendbuf[1024] = {0};
	char recvbuf[1024] = {0};
	while (1)
	{
		FD_ZERO(&rset);
		FD_SET(stdin_fd, &rset);
		FD_SET(sockfd, &rset);
	
		nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
		if (nready == -1)
		{
			if (errno == EINTR)
				continue;

			ERR_EXIT("select");
		}

		if (FD_ISSET(stdin_fd, &rset))
		{
			if (fgets(sendbuf, sizeof(sendbuf), stdin) == NULL)
				break;

			writen(sockfd, sendbuf, strlen(sendbuf));
			memset(&sendbuf, 0, sizeof(sendbuf));
		}

		if (FD_ISSET(sockfd, &rset))
		{
			ret = readline(sockfd, recvbuf, sizeof(recvbuf));
			if(ret < 0)
				ERR_EXIT("readline");
			else if(ret == 0)
			{
				printf("server close\n");
				break;
			}

			printf("server : %s", recvbuf);
			memset(&recvbuf, 0, sizeof(recvbuf));
		}
	}
}

int
main(void)
{
	int sockfd;
	if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
		ERR_EXIT("socket");
	
	struct sockaddr_un servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sun_family = AF_UNIX;
	strcpy(servaddr.sun_path, UNIX_DOMAIN_PATH);

	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)))
		ERR_EXIT("connect");

	echo_cli(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	return 0;
}
