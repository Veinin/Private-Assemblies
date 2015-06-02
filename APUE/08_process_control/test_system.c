/**
system调用了fork(失败 < 0),exec(成功 _exit(127)),waitpid(返回0)三种函数，因此有三种返回值
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int
main(void) {
	int status;

	if((status = system("date")) < 0)
		printf("system() error\n");

	exit(0);
}