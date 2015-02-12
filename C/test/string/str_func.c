#include <stdio.h>
#include <string.h>
#include <ctype.h>

void strbasic();
void strfind();
void charoperation();
void memoperation();

int
main(void) {
	strbasic();
	printf("--------------\n");
	strfind();
	printf("--------------\n");
	charoperation();
	printf("--------------\n");
	memoperation();
	return 0;
}

void
strbasic() {
	//strlen
	char a[] = "hello";
	printf("a length : %ld\n", strlen(a));

	//strcpy
	char b[] = "world";
	strcpy(a, b);
	printf("a str : %s\n", a);

	//strcat
	char c[20] = "hello";
	strcat(c, " world!");
	printf("c str : %s\n", c);

	//strcmp
	if(strcmp(a, b) == 0) {
		printf("a equal b\n");
	} else {
		printf("a not equal b\n");
	}
	
	//strncpy strncat
	char e[40];
	char f[20] = "veinin";
	char g[20] = "Guo";
	strncpy(e, f, 5);
	strncat(e, g, 3);
	printf("e str : %s\n", e);
	
	//strncmp
	char h[] = "Guodx";
	printf("e strncmp b : %u\n", strncmp(g, h, 3));
}

void
strfind() {
	char *s = "veinin guo";
	
	//strchr
	char *strc = strchr(s, 'i');
	printf("find strc : %s\n", strc);
	
	//strrchr
	char *strr = strrchr(s, 'i');
	printf("find strr : %s\n", strr);

	//strstr 查找子串
	char *find = "guo";
	char *f = strstr(s, find);
	printf("find strstr : %s\n", f);
}


void
charoperation() {
	char a;
	//iscntrl 任何控制字符
	a = 0x0d;
	printf("iscntrl : %s\n", iscntrl(a) ? "true" : "false");

	//isspace 空白字符
	a = ' ';
	printf("iscntrl : %s\n", isspace(a) ? "true" : "false");

	//isdigit 十进制
	a = '3';
	printf("iscntrl : %s\n", isdigit(a) ? "true" : "false");

	//isxdigit 十六进制
	a = 'a';
	printf("iscntrl : %s\n", isxdigit(a) ? "true" : "false");

	//islower 小写字母
	printf("iscntrl : %s\n", islower(a) ? "true" : "false");
	
	//isupper 大写字母
	a = 'A';
	printf("iscntrl : %s\n", isupper(a) ? "true" : "false");

	//isalpha 字母a~z A~Z
	printf("iscntrl : %s\n", isalpha(a) ? "true" : "false");

	//isalnum 字母或数字
	printf("iscntrl : %s\n", isalnum(a) ? "true" : "false");

	//ispunct 标点符号
	a = ',';
	printf("iscntrl : %s\n", ispunct(a) ? "true" : "false");

	//isgraph 任何图形字符
	a = '@';
	printf("iscntrl : %s\n", isgraph(a) ? "true" : "false");

	//isprint 任何可以打印字符
	a = 0x20;
	printf("iscntrl : %s\n", isprint(a) ? "true" : "false");
}

#define SIZE 50

void
memoperation() {
	char temp[SIZE], values[SIZE] = "hello, world.";

	//memcpy, copy values to temp
	memcpy(temp, values, sizeof(values));
	printf("memcpy temp : %s\n", temp);

	//memmove, move the values to temp2, 与memcpy相似
	char temp2[SIZE];
	memmove(temp2, values, sizeof(values));
	printf("memmove temp : %s\n", temp2);

	//memcmp, compare 
	char *temp3 = "ha";
	int ret = memcmp(temp3, values, 2);
	printf("compare temp3 and values, ret value : %d\n", ret);

	//memchr, find ch in values
	int ch = 'o';
	char *retC = memchr(values, ch, sizeof(values));
	if(retC) {
		printf("find succ : %s\n", retC);
	} else {
		printf("not found ch!");
	}

	//memset, set the str to ch where length of 5
	memset(temp, 0, sizeof(temp));
	printf("memset the temp, temp : %s\n", temp);
}

