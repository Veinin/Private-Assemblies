#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t ntid;

void
printids(const char *s) {
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();	//获取自身线程ID
	printf("%s pid : %lu tid : %lu (0x%lx)\n", s, (unsigned long)pid,
		(unsigned long)tid, (unsigned long)tid);
}

void *
thr_fn(void *arg) {
	printids("new thread.");
	return (void *)(0);
}

int
main(void) {
	int err;

	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	if(err) {
		printf("can't create thread.\n");
		exit(0);
	}

	printf("main thread\n");
	sleep(1);	//等待子线程结束
	exit(0);
}