#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <string.h>

#define MAXLINE 1024

void do_line(char *);
void cmd_add(void);
int get_token(void);

jmp_buf jmpbuffer;

int
main(void)
{
	char line[MAXLINE];

	if(setjmp(jmpbuffer) != 0)
		printf("setjmp : error!\n");

	while(fgets(line, MAXLINE, stdin) != NULL)
		do_line(line);

	exit(0);
}

char *tok_ptr;

void
do_line(char *prt) {
	printf("do_line : %s", prt);

	tok_ptr = prt;
	int token = get_token();
	printf("token : %d\n", token);

	printf("do_line end...\n");
}

int
get_token(void)
{
	if(strstr(tok_ptr, "hello") != NULL)
		return 1;
	else
		longjmp(jmpbuffer, 1); //发生错误时，跳转
}
