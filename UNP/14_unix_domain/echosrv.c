#include "../unp.h"

int main(void)
{
	int listenfd;

	if ((listenfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
		ERR_EXIT("socket");
	
	struct sockaddr_un servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sun_family = AF_UNIX;
	strcpy(servaddr.sun_path, UNIX_DOMAIN_PATH);

	unlink(UNIX_DOMAIN_PATH); //绑定前删除Unix套接字文件

	if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
		ERR_EXIT("bind");

	if (listen(listenfd, SOMAXCONN) < 0)
		ERR_EXIT("listen");


	int i, nready, ret;
	int client[FD_SETSIZE] = {0};
	for (i = 0; i < FD_SETSIZE; i++)
		client[i] = -1;

	int maxi = 0;
	int maxfd = listenfd;
	fd_set allset;
	fd_set rset;
	FD_ZERO(&allset);
	FD_ZERO(&rset);
	FD_SET(listenfd, &allset);

	int connfd;
	struct sockaddr_in peeraddr;
	socklen_t peeraddrlen;

	while (1)
	{
		rset = allset;
		nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
		if (nready == -1)
		{
			if (errno == EINTR)
				continue;

			ERR_EXIT("select");
		}

		if (FD_ISSET(listenfd, &rset))
		{
			peeraddrlen = sizeof(peeraddr);
			connfd = accept(listenfd, (struct sockaddr*)&peeraddr, &peeraddrlen);
			if (connfd < 0)
				ERR_EXIT("accept");
		
			printf("ip : %s prot : %d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));

			for (i = 0; i < FD_SETSIZE; i++)
			{
				if(client[i] == -1)
				{
					client[i] = connfd;
					if (i > maxi)
						maxi = i;
					break;
				}
			}
			
			if (i == FD_SETSIZE)
			{
				fprintf(stderr, "to many client\n");
				exit(EXIT_FAILURE);
			}

			FD_SET(connfd, &allset);
			if (connfd > maxfd)
				maxfd = connfd;

			if (--nready <= 0)
				continue;
		} 

		for (i = 0; i <= maxi; i++)
		{
			connfd = client[i];
			if (FD_ISSET(connfd, &rset))
			{
				char recvbuf[1024] = {0};
				ret = readline(connfd, recvbuf, sizeof(recvbuf));
				if (ret < 0)
					ERR_EXIT("readline");
				else if(ret == 0)
				{
					printf("client close\n");
					FD_CLR(connfd, &allset);
					close(connfd);
					client[i] = -1;
				}

				printf("client : %s", recvbuf);
				writen(connfd, recvbuf, strlen(recvbuf));

				if (--nready <= 0)
					break;
			}
		}
	}

	close(listenfd);

	return 0;
}
