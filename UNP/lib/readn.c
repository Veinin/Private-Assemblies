#include "../unp.h"

size_t readn(int fd, void *buf, size_t count)
{
	size_t nleft = count;
        size_t nread;
	char *bufp = (char*)buf;

	while(nleft > 0)
	{
		if((nread = read(fd, buf, nleft)) < 0)
		{
			if(errno == EINTR)
				continue;
			return -1;
		}
		else if(nread == 0)
			return count - nleft;

		bufp += nread;
		nleft -= nread;
	}
}
