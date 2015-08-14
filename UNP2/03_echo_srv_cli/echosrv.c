#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)

int main(void) 
{
	int listenfd;
	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ERR_EXIT("socket");

	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8888);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
		ERR_EXIT("bind");

	if(listen(listenfd, SOMAXCONN) < 0)
		ERR_EXIT("listen");

	int connfd;
	struct sockaddr_in cliaddr;
	socklen_t cliaddrlen = sizeof(cliaddr);
	if((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddrlen)) < 0)
		ERR_EXIT("accept");
	else
		printf("client connect. ip address : %s\n", inet_ntoa(cliaddr.sin_addr));

	char recvbuf[1024];
	while(1)
	{
		memset(&recvbuf, 0, sizeof(recvbuf));
		int ret = read(connfd, recvbuf, sizeof(recvbuf));
		printf("receive from cliend, message : %s", recvbuf);
		write(connfd, recvbuf, ret);
	}

	close(listenfd);
	close(connfd);

	return 0;
}
