#include "../unp.h"

size_t writen(int fd, const void *buf, size_t count)
{
	size_t nleft = count;
	size_t nwrite;
	char *bufp = (char*)buf;

	while (nleft > 0)
	{
		if ((nwrite = write(fd, buf, nleft)) < 0)
		{
			if (errno == EINTR)
				continue;
			return -1;
		}
		else if (nwrite == 0)
			return count - nleft;

		bufp += nwrite;
		nleft -= nwrite;
	}

	return count;
}
