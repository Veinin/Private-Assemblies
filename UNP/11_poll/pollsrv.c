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
	struct pollfd client[POLL_FD_SIZE];
	int maxi = 0;

	for (i = 0; i < POLL_FD_SIZE; i++)
		client[i].fd = -1;

	int nready;
	int connfd;
	struct sockaddr_in peeraddr;
	socklen_t peeraddrlen;

	//设置监听套接字可读事件
	client[0].fd = listenfd;
	client[0].events = POLLIN;

	int count = 0;	//连接计数
	while (1)
	{
		nready = poll(client, maxi + 1, -1); 
		if (nready == -1)
		{
			if (errno == EINTR)
				continue;	//信号中断，重启

			ERR_EXIT("poll");
		}

		if (nready == 0)	//超时时会返回0
			continue;

		if(client[0].revents & POLLIN)	//POLLIN标志产生可读事件，客户端发起连接
		{
			peeraddrlen = sizeof(peeraddr);
			connfd = accept(listenfd, (struct sockaddr*)&peeraddr, &peeraddrlen);	
			if (connfd == -1)
				ERR_EXIT("accept");

			printf("ip : %s, port : %d count : %d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port), ++count);

			for (i = 0; i < POLL_FD_SIZE; i++)
			{
				if(client[i].fd == -1)
				{
					client[i].fd = connfd;
					client[i].events = POLLIN;
					if(i > maxi)
						maxi = i;
					break;
				}
			}

			if (i == POLL_FD_SIZE)
			{
				printf("i = %d\n", i);
				fprintf(stderr, "to many clients\n");
				exit(EXIT_FAILURE);
			}

			if (--nready <= 0)
				continue;
		}

		for(i = 1; i <= maxi; i++)
		{
			connfd = client[i].fd;
			if (connfd == -1)
				continue;
			
			if (client[i].revents & POLLIN)
			{
				char recvbuf[1024] = {0};
				ret = readline(connfd, recvbuf, sizeof(recvbuf));
				if(ret < 0)
					ERR_EXIT("readline");
				else if(ret == 0)
				{
					printf("client close\n");
					close(connfd);
					client[i].fd = -1;
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
