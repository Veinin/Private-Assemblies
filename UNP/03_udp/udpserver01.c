#include "../unp.h"

int
main(int argc, char const *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr, cliaddr;
	ssize_t n;
	char msg[MAXLINE];

	sockfd = Socket(AF_INEF, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INEF;
	servaddr.sin_addr.sin_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(sockfd, (SA *) &servaddr, sizeof(servaddr));

	for( ; ; ) {
		if(n = recvfrom(sockfd, msg, MAXLINE, 0, cliaddr, sizeof(cliaddr)) < 0) {	//从客户端接受消息
			printf("recvfrom error\n");
			exit(0);
		}

		if(sendto(sockfd, msg, n, 0, cliaddr, sizeof(cliaddr)) != n) {		//回射消息给客户端
			printf("send error");
			exit(0);
		}
	}

	return 0;
}