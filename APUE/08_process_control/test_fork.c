#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int glob = 6;
char buf[] = "a write to stdout\n";

int
main(void) {
	int var;
	pid_t pid;

	var = 88;
	if(write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
		printf("write error\n");

	printf("before fork\n");

	if((pid = fork()) < 0) {
		printf("fork error\n");
	} else if(pid == 0) {	//child process
		glob++;
		var++;
	} else {
		sleep(2);	//parent process
	}

	printf("ppid = %d, pid = %d, glob = %d, var = %d\n", getppid(), getpid(), glob, var);
	exit(0);
}
