#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int 
main() {
	pid_t pid;

	if((pid = fork()) < 0) {
		printf("fork error\n");
	} else if(pid == 0) {	//first child
		if((pid = fork()) < 0) {
			printf("fork error\n");
		} else if(pid > 0) {
			printf("first child process exit! parent pid = %d\n", getppid());
			exit(0);	//first child exit
		}


		sleep(2);
		printf("second child process exit, parrent pid = %d\n", getppid());
		exit(0);
	}

	if(waitpid(pid, NULL, 0) != pid)
		printf("waitpid error!\n");
	else
		printf("waitpid first child process exit, pid = %d\n", pid);

	exit(0);	//parent process exit
}