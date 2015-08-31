#include "../unp.h"

int
write_timeout(int fd, unsigned int wait_seconds)
{
	int ret = 0;

	if (wait_seconds > 0)
	{
		fd_set write_fdset;
		
		FD_ZERO(&write_fdset);
		FD_SET(fd, &write_fdset);

		struct timeval timeout;
		timeout.tv_sec = wait_seconds;
		timeout.tv_usec = 0;

		do
		{
			ret = select(fd + 1, NULL, &write_fdset, NULL, &timeout);
		} while (ret < 0 && errno == EINTR);

		if (ret == 0)
		{
			ret = -1;
			errno = ETIMEDOUT;
		}
		else if (ret == 1)
			ret = 0;
	}

	return ret;
}
