/**
 * readn_writen
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

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

struct packet
{
        int len;        //包头
	char buf[1024]; //包缓冲区
};

size_t readn(int fd, void *buf, size_t count)
{
	size_t nleft = count;
	size_t nread;
	char *bufp = (char*)buf;

	while(nleft > 0)
	{
		if((nread = read(fd, buf, nleft)) < 0)
		{
			if(errno == EINTR)
				continue;
			return -1;
		}
		else if(nread == 0)
			return count - nleft;

		bufp += nread;
		nleft -= nread;
	}

	return count;
}

size_t writen(int fd, const void *buf, size_t count)
{
	size_t nleft = count;
	size_t nwrite;
	char *bufp = (char*)buf;

	while(nleft > 0)
	{
		if((nwrite = write(fd, buf, nleft)) < 0)
		{
			if(errno == EINTR)
				continue;
			return -1;
		}
		else if(nwrite == 0)
			return count - nleft;

		bufp += nwrite;
		nleft -= nwrite;
	}

	return count;
}

void do_service(int connfd)
{
	struct packet recvbuf;
	int n;
	while(1)
	{
		memset(&recvbuf, 0, sizeof(recvbuf));
		int ret = readn(connfd, &recvbuf.len, 4);
		if(ret == -1)
			ERR_EXIT("read");
		else if(ret < 4)
		{
			printf("client close\n");
			break;
		}
		
		n = ntohl(recvbuf.len);
		ret = readn(connfd, &recvbuf.buf, n);
		if(ret == -1)
			ERR_EXIT("read");
		else if(ret < n)
		{
			printf("client close\n");
			break;
		}

		printf("client message : %s", recvbuf.buf);
		writen(connfd, &recvbuf, 4 + n);
	}
}

int main(void)
{
	int listenfd;
	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ERR_EXIT("socket");

	struct sockaddr_in srvaddr;
	memset(&srvaddr, 0, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(8888);
	srvaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int on = 1;
	if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
		ERR_EXIT("setsockopt");

	if(bind(listenfd, (struct sockaddr*)&srvaddr, sizeof(srvaddr)) < 0)
		ERR_EXIT("bind");

	if(listen(listenfd, SOMAXCONN) < 0)
		ERR_EXIT("listen");

	struct sockaddr_in cliaddr;
	socklen_t cliaddrlen = sizeof(cliaddr);
	int connfd;
	
	pid_t pid;
	while(1)
	{
		if((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddrlen)) < 0)
			ERR_EXIT("accept");

		printf("new client ip : %s, port : %d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

		pid = fork();
		if(pid < 0)
			ERR_EXIT("fork");
		else if(pid == 0) 
		{
			close(listenfd);
			do_service(connfd);
			exit(EXIT_SUCCESS);
		} else 
			close(connfd);

	}

	close(listenfd);

	return 0;
}
