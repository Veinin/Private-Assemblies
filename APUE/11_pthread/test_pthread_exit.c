#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct foo {
	int a, b, c;
};

void
err_exit(int errorCode, const char * s) {
	printf("%s, errorCode : %d\n", s, errorCode);
	exit(0);
}

void
printfoo(const char *s, const struct foo *fp) {
	printf("%s", s);
	printf("struct at 0x%lx\n", (unsigned long) fp);
	printf("foo.a = %d\n", fp->a);
	printf("foo.b = %d\n", fp->b);
	printf("foo.c = %d\n", fp->c);
}

void *
thr_fn1(void *arg) {
	struct foo f = {1, 2, 3};	//堆数据返回给主函数，该数据可能已丢失
	printfoo("thread 1 : \n", &f);
	pthread_exit((void *) &f);
}

void *
thr_fn2(void *arg) {
	printf("thread 2 : ID is %lu\n", (unsigned long) pthread_self());
	pthread_exit((void *) 0);
}

int 
main(void) {
	int err;
	pthread_t tid1, tid2;
	struct foo *fp;

	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if(err != 0)
		err_exit(err, "can't create thread 1");

	err = pthread_join(tid1, (void *) &fp);
	if(err != 0)
		err_exit(err, "can't join with thread 1");

	sleep(1);
	printf("parent starting second thread\n");

	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if(err != 0)
		err_exit(err, "can't create thread 2");

	sleep(1);
	printfoo("parent : \n", fp);	//父进程试图访问已释放的内存，发生错误（MACOS : Segmentation fault: 11）
	exit(0);
}
