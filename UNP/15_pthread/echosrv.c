/**
 * thread per connection
 * 一个链接一个线程处理并发，服务器的主线程负责监听，接受客户端连接; 其他线程负责处理客户端的通信。
 */
#include "../unp.h"
#include <pthread.h>

void do_service(int connfd)
{
	char recvbuf[1024];
	while(1)
	{
		memset(&recvbuf, 0, sizeof(recvbuf));
		int ret = read(connfd, recvbuf, sizeof(recvbuf));
		if(ret == 0)
		{
			printf("server close\n");
			close(connfd);
			break;
		}
		else if(ret == -1)
			ERR_EXIT("read");
		printf("client : %s", recvbuf);
		write(connfd, recvbuf, ret);
	}
}

void* thread_routine(void *arg) 
{
	pthread_detach(pthread_self());	//设置分离状态，防止僵死线程
	int connfd = *((int*)arg);
	free(arg);
	do_service(connfd);
	printf("exiting thread...\n");
	return NULL;
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

		printf("ip : %s, port : %d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

		int *p = malloc(sizeof(int));
		*p = connfd;
		pthread_t tid;
		int ret;
		if ((ret = pthread_create(&tid, NULL, thread_routine, (void*)p)) != 0)
		{
			fprintf(stderr, "pthread_create : %s\n", strerror(ret));
			exit(EXIT_FAILURE);
		}
	}

	close(listenfd);

	return 0;
}
