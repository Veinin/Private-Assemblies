#include "../unp.h"

void
echo_srv(int sockfd)
{
	struct sockaddr_in peeraddr;
	socklen_t peeraddrlen;
	char recvbuf[1024] = {0};
	while (1)
	{
		memset(&recvbuf, 0, sizeof(recvbuf));
		peeraddrlen = sizeof(peeraddr);
		int n = recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr*)&peeraddr, &peeraddrlen);
		if (n < 0)
		{
			if(errno == EINTR)
				continue;

			ERR_EXIT("recvfrom");
		}
		else if (n > 0)
		{
			printf("ip : %s, port : %d, msg : %s\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port), recvbuf);
			sendto(sockfd, recvbuf, strlen(recvbuf), 0, (struct sockaddr*)&peeraddr, sizeof(peeraddr));
		}
	}

	close(sockfd);
}

int
main(void)
{
	int sockfd;

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		ERR_EXIT("sock");

	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		ERR_EXIT("bind");

	echo_srv(sockfd);
	
	return 0;
}
