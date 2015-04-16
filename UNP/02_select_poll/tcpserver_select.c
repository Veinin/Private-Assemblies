#include "../unp.h"

int
main(int argc, char **argv)
{
	int 	i, maxi, maxfd, listenfd, connfd, sockfd;
	int 	nready, client[FD_SETSIZE];
	ssize_t n;
	fd_set  rset, allset;
	char buf[MAXLINE];
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, ssize_t(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(&servaddr, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	//初始化描述符集合
	maxfd = listenfd;
	maxi = -1;
	for(i = 0; i < FD_SETSIZE; i++)
		client[i] = -1;

	//设置select的监听套接字描述符
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);

	for( ; ;) {
		rset = allset;
		nready = Select(maxfd + 1, &rset, NULL, NULL, NULL);	//设置select读描述符

		if(FD_ISSET(listenfd, &set)) {	//新连接建立，监听套接字可读
			clilen = sizeof(cliaddr);
			connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);

			for(i = 0; i < FD_SETSIZE; i++) {	//记录新连接套接字
				if(client[i] < 0) {
					client[i] = connfd;
					break;
				}
			}

			if(i == FD_SETSIZE)
				err_quit("too many clients.");

			FD_SET(&connfd, &allset);
			if(connfd > maxfd)
				maxfd = connfd;

			if(i > maxi)
				maxi = i;

			if(--nready <= 0)	//就绪描述符减1，如为0，跳过下一次循环，避免检查未就绪描述符
				continue;
		}

		for(i = 0; i < maxi; i++) {
			if( (sockfd = client[i]) < 0)
				continue;

			if(FD_ISSET(sockfd, &rset)) {
				if( (n = Read(sockfd, buf, MAXLINE)) == 0) {	//客户端关闭连接
					Close(sockfd);
					FD_CLR(sockfd, &allset);	//从select中关闭描述符
					client[i] = -1;
				} else {
					Writen(sockfd, buf, n);
				}

				if(--nready <= 0)
					break;
			}
		}
		
	}


}