#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define MAXLINE 1024

static void sig_alrm(int);

int main(void)
{
	int n;
	char line[MAXLINE];

	if(signal(SIGALRM, sig_alrm) == SIG_ERR)
		printf("signal (SIGALRM) error");
	
	alarm(10);
	if((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
		printf("read error");
	alarm(0);

	write(STDOUT_FILENO, line, n);

	return 0;
}

static void
sig_alrm(int signo)
{
	return;
}