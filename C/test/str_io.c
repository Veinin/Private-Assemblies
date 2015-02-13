#include <stdio.h>
#include <string.h>

void getchar_putchar();
void gets_puts();
void fgets_fputs();
void scanf_printf();
void sprintf_test();

int
main(void) {
	printf("----gets_puts----\n");
	fgets_fputs();

	printf("----getchar putchar----\n");
	getchar_putchar();

	printf("----gets_puts----\n");
	gets_puts();

	printf("----scanf_printf----\n");
	scanf_printf();	

	printf("----sprintf_test----\n");
	sprintf_test();

	return 0;
}

void getchar_putchar() {
	//input a character
	char ch = getchar();

	//output a character
	putchar(ch);
	putchar('\n');
}

void gets_puts() {
	puts("Don't recomment use gets, can use the fgets instead.");
} 

void fgets_fputs() {
	char line[81];
	fgets(line, 81, stdin);
	fputs(line, stdout);
}

void scanf_printf() {
	char firstname[8], lastname[15];
	scanf("%8s %15s", firstname, lastname);
	printf("firstname : %s, lastname : %s\n", firstname, lastname);
}

void sprintf_test() {
	char first[81];
	char last[81];
	char format[162];

	fputs("enter the first string.\n", stdout);
	scanf("%s", first);
	
	fputs("enter the last string.\n", stdout);
	scanf("%s", last);

	sprintf(format, "first : %s, last : %s", first, last);
	puts(format);
}
