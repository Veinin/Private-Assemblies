#include "../unp.h"

void sig_chld(int);

int 
main(int argc, char **argv)
{
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, serveraddr;
	void sig_chld(int);

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERV_PORT);

	Bind(listenfd, (SA *) &serveraddr, sizeof(serveraddr));
	Listen(listenfd, LISTENQ);
	Signal(SIGCHLD, sig_chld);

	for( ; ; ) {
		clilen = sizeof(cliaddr);
		if((connfd = Accept(listenfd, (SA *) &serveraddr, &clilen)) < 0) {
			if(errno == EINTR)
				continue;
			else
				err_sys("accept error");
		}

		if((childpid = Fork()) == 0) {
			Close(listenfd);
			str_echo(connfd);
			exit(0);
		}

		Close(connfd);
	}
}

void
sig_chld(int signo)
{
	pid_t pid;
	int stat;

	while((pid == waitpid(-1, &stat, WNOHANG)) > 0) {
		printf("child %d terminated\n", pid);
	}

	return;
}