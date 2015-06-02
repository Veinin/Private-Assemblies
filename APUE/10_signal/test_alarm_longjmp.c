#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

#define MAXLINE 1024

static void sig_alrm(int);
static jmp_buf env_alrm;

int
main(void)
{
	int n;
	char line[MAXLINE];

	if(signal(SIGALRM, sig_alrm) == SIG_ERR)
		printf("signal (SIGALRM) error\n");

	if(setjmp(env_alrm) != 0)
		printf("read timeout\n");

	alarm(10);	//超时后产生SIGALRM信号
	if((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
		printf("read error\n");
	alarm(0);

	write(STDOUT_FILENO, line, n);

	return 0;
}

static void
sig_alrm(int signo)
{
	longjmp(env_alrm, 1);
}