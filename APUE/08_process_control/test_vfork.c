#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int glob = 6;

int
main(void)
{
	int var;
	pid_t pid;

	var = 88;
	printf("before vfork\n");
	if((pid = fork()) < 0) {
		printf("vfork error\n");
	} else if(pid == 0) {	//child process
		glob++;
		var++;
		_exit(0);
	}

	//parent process continues here.
	printf("ppid = %d, pid = %d, glob = %d, var = %d\n", getppid(), getpid(), glob, var);
	exit(0);
}
