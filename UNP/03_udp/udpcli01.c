#include "../unp.h"

void dg_client(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen);

int
main(int argc, char const *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr;

	if(argc != 2) {
		printf("usage : udpcli01 <IPaddress>\n");
		exit(0);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	dg_client(stdin, sockfd, (SA *) &servaddr, sizeof(servaddr));

	exit(0);
}

void dg_client(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen) {
	int n;
	char sendline[MAXLINE], recvline[MAXLINE + 1];

	while(fgets(sendline, MAXLINE, fp) != NULL) {
		n = strlen(sendline);
		if(sendto(sockfd, sendline, n, 0, pservaddr, servlen) != n) {	//发送消息给服务端
			printf("sendto error\n");
			exit(0);
		}

		if( (n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL)) < 0) {		//接受服务端回射消息
			printf("recvfrom error\n");
			exit(0);
		}

		recvline[n] = 0;
		fputs(recvline, stdout);
	}
}