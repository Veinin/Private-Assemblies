#ifndef UNP_H
#define UNP_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <unistd.h>

#define SERV_PORT 8888

#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)

size_t readn(int fd, void *buf, size_t count);
size_t writen(int fd, const void *buf, size_t count);

#endif
