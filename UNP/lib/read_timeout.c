#include "../unp.h"

int
read_timeout(int fd, unsigned int wait_seconds)
{
	int ret = 0;

	if (wait_seconds > 0)
	{
		fd_set read_fdset;

		FD_ZERO(&read_fdset);
		FD_SET(fd, &read_fdset);

		struct timeval timeout;
		timeout.tv_sec = wait_seconds;
		timeout.tv_usec = 0;

		do
		{
			ret = select(fd + 1, &read_fdset, NULL, NULL, &timeout);
		} while (ret < 0 && errno == EINTR);

		if (ret == 0)		//不可读，超时
		{
			ret = -1;
			errno = ETIMEDOUT;
		}
		else if (ret == 1)	//可读
			ret  = 0;
	}

	return ret;
}
