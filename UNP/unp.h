#ifndef UNP_H
#define UNP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <netdb.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <arpa/inet.h>

#define SERV_PORT 8888
#define POLL_FD_SIZE 2048

#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)

size_t readn(int fd, void *buf, size_t count);
size_t writen(int fd, const void *buf, size_t count);
size_t readline(int sockfd, void *buf, size_t maxline);

int gethostaddr(char *addr);

int read_timeout(int fd, unsigned int wait_seconds);
int write_timeout(int fd, unsigned int wait_seconds);
int accept_timeout(int fd, struct sockaddr_in *addr, unsigned int wait_seconds);

#endif
