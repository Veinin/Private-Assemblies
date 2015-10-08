#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_routine(void *arg)
{
	int i;
	for (i = 0; i < 10; i++)
	{
		printf("B ");
		fflush(stdout);

		if (i == 3)
			pthread_exit("ABC");
	}

	return 0;
}

int main(void)
{
	pthread_t tid;
	int ret;

	if ((ret = pthread_create(&tid, NULL, thread_routine, NULL)) != 0)
	{
		fprintf(stderr, "pthread_create : %d\n", strerror(ret));
		exit(EXIT_FAILURE);
	}

	int i;
	for (i = 0; i < 10; i++)
	{
		printf("A ");
		fflush(stdout);
	}

	void* value;
	if ((ret = pthread_join(tid, &value)) != 0)
	{
		fprintf(stderr, "pthread_join:%d\n", strerror(ret));
		exit(EXIT_FAILURE);
	}
	printf("\n");
	printf("return msg = %s\n", (char*)value);

	return 0;
}

