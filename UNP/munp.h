#ifndef	_munp_h
#define	_munp_h

#include	<sys/types.h>
#include	<sys/socket.h>
#include	<sys/time.h>

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#define	SA	struct sockaddr
#define	SERV_PORT	8888
#define	MAXLINE		4096

void	err_dump(const char *, ...);
void	err_msg(const char *, ...);
void	err_quit(const char *, ...);
void	err_ret(const char *, ...);
void	err_sys(const char *, ...);

#endif