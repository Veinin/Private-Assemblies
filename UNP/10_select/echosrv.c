/**
 * select - server
 */
#include "../unp.h"

int
main(void)
{
	int listenfd;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ERR_EXIT("socket");

	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int on = 1;
	if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
		ERR_EXIT("setsockopt");

	if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
		ERR_EXIT("bind");

	if (listen(listenfd, SOMAXCONN) < 0)
		ERR_EXIT("listen");

	int i, ret;
	int client[FD_SETSIZE];
	int maxi = 0;

	for (i = 0; i < FD_SETSIZE; i++)
		client[i] = -1;

	int nready;
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
				continue;	//信号中断，重启

			ERR_EXIT("select");
		}

		if (nready == 0)	//超时时会返回0
			continue;

		if(FD_ISSET(listenfd, &rset))	//客户端发起连接
		{
			peeraddrlen = sizeof(peeraddr);
			connfd = accept(listenfd, (struct sockaddr*)&peeraddr, &peeraddrlen);	
			if (connfd == -1)
				ERR_EXIT("accept");

			printf("ip : %s, port : %d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));

			for (i = 0; i < FD_SETSIZE; i++)
			{
				if(client[i] == -1)
				{
					client[i] = connfd;
					if(i > maxi)
						maxi = i;
					break;
				}
			}


			if (i == FD_SETSIZE)
			{
				fprintf(stderr, "to many clients\n");
				exit(EXIT_FAILURE);
			}

			FD_SET(connfd, &allset);
			if (connfd > maxfd)
				maxfd = connfd;

			if (--nready <= 0)
				continue;
		}

		for(i = 0; i <= maxi; i++)
		{
			connfd = client[i];
			if (connfd == -1)
				continue;
			
			if (FD_ISSET(connfd, &rset))
			{
				char recvbuf[1024] = {0};
				ret = readline(connfd, recvbuf, sizeof(recvbuf));
				if(ret < 0)
					ERR_EXIT("readline");
				else if(ret == 0)
				{
					printf("client close\n");
					FD_CLR(connfd, &allset);	//客户端关闭，删除
					close(connfd);
					client[i] = -1;
				}

				printf("client : %s", recvbuf);
				writen(connfd, recvbuf, strlen(recvbuf));

				if(--nready <= 0)
					break;
			}
		}
	}
	
	return 0;
}
