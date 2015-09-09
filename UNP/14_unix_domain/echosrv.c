#include "../unp.h"

#define

int main(void)
{
	int listenfd;

	unlink(UNIX_DOMAIN_SOCKET_NAME);

	if ((listenfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
		ERR_EXIT("socket");
	
	struct sockaddr_un servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sun_family = AF_UNIX;
	strcpy(servaddr.sun_path, UNIX_DOMAIN_SOCKET_NAME);

	if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
		ERR_EXIT("bind");

	if (listen(listenfd, SOMAXCONN) < 0)
		ERR_EXIT("listen");


	int i, nready;
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
			if (errno = EINTR)
				continue;

			ERR_EXIT("select");
		}

		if (FD_ISSET(listenfd, &rset))
		{
			peeraddrlen = sizeof(peeraddr);
			connfd = accept(listenfd, (struct sockaddr*)&peeraddr, peeraddrlen);
			if (connfd < 0)
				ERR_EXIT("accept");
			
			for (i = 0; i < FD_SETSIZE; i++)
			{
				if(client[i] == -1)
				{
					client[i] = connfd;
					if (i > maxi)
						maxi = connfd;
					break;
				}
			}
			
			if (i == FD_SETSIZE)
			{
				fprintf(stderr, "to many client\n");
				exit(EXIT_FAILURE);
			}

			FD_SET(connfd, &rset);
			if (connfd > maxfd)
				maxfd = connfd;

			if (--nready <= 0)
				continue;
		} 
	}
}
