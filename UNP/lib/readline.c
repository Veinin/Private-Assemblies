#include "../unp.h"

static size_t
recv_peek(int sockfd, void *buf, size_t len)
{
	while (1)
	{
		int ret = recv(sockfd, buf, len, MSG_PEEK); //从缓冲区读取数据，MSG_PEEK选项不会清除缓冲区数据
		if (ret == -1 && errno == EINTR)
			continue;
		return ret;
	}
}

size_t
readline(int sockfd, void *buf, size_t maxline)
{
	int ret;
	int nread;
	char *bufp = (char*)buf;
	int nleft = maxline;
	while (1)
	{
		if ((ret = recv_peek(sockfd, bufp, nleft)) < 0)
			return ret;
		else if (ret == 0)
			return ret;

		nread = ret;
		int i;
		for (i = 0; i < nread; i++)
		{
			if (bufp[i] == '\n')	//找到\n标记，直接返回
			{
				ret = readn(sockfd, bufp, i + 1);
				if (ret != i + 1)
					exit(EXIT_FAILURE);

				return ret;
			}
		}

		if (nread > nleft)
			exit(EXIT_FAILURE);

		//没有找到\n标记，全部读出
		nleft -= nread;
		ret = readn(sockfd, bufp, nread);
		if (ret != nread)
			exit(EXIT_FAILURE);
		
		bufp += nread;
	}

	return -1;
}
