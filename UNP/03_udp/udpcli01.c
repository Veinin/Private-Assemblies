#include "../unp.h"

int
main(int argc, char const *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr;
	size_t n;
	char sendline[MAXLINE], recvline[MAXLINE + 1];

	if(argc != 2) {
		printf("usage : udpcli01 <IPaddress>\n");
		exit(0);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVER_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	sockfd = Socket(sockfd, (SA *) &servaddr, sizeof(servaddr));

	while(fgets(sendline, n, stdin) != NULL) {
		if(sendto(sockfd, sendline, n, 0, servaddr, sizeof(servaddr)) != n) {	//发送消息给服务端
			printf("sendto error\n");
			exit(0);
		}

		if( (n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL)) < 0) {		//接受服务端回射消息
			printf("recvfrom error\n");
			exit(0);
		} 

		recvfrom[n] = 0;
		fputs(recvline, stdout);
	}

	exit(0);
}