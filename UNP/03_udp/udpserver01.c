#include "../unp.h"

void dg_server_echo(int sockfd, SA *pcliaddr, socklen_t clilen);

int
main(int argc, char const *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr, cliaddr;

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(sockfd, (SA *) &servaddr, sizeof(servaddr));

	dg_server_echo(sockfd, (SA *) &cliaddr, sizeof(cliaddr));

	return 0;
}

void dg_server_echo(int sockfd, SA *pcliaddr, socklen_t clilen) {
	int n;
	socklen_t len;
	char mesg[MAXLINE];

	for( ; ; ) {
		len = clilen;
		if((n = recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len)) < 0) {	//从客户端接受消息
			printf("recvfrom error\n");
			exit(0);
		}

		if(sendto(sockfd, mesg, n, 0, pcliaddr, len) != n) {		//回射消息给客户端
			printf("send error");
			exit(0);
		}
	}
}