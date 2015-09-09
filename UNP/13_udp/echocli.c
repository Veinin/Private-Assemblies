#include "../unp.h"

void
echo_cli(int sockfd, const struct sockaddr *servaddr, socklen_t servaddrlen)
{
	int ret;
	char sendbuf[1024] = {0};
	char recvbuf[1024] = {0};

	while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
	{
		sendto(sockfd, sendbuf, strlen(sendbuf), 0, servaddr, servaddrlen);

		ret = recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0, NULL, NULL);
		if (ret < 0)
		{
			if (errno == EINTR)
				continue;
			ERR_EXIT("recvfrom");
		}
		printf("echo msg : %s", recvbuf);

		memset(&sendbuf, 0, sizeof(sendbuf));
		memset(&recvbuf, 0, sizeof(recvbuf));
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
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));	//调用connect，维护本地连接状态

	echo_cli(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	return 0;
}
