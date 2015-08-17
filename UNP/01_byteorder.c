/**
 * 主机字节序-网络字节序转换
 * 大端字节序：最高有效位存储与最低内存地址，最低有效位存储与最高内存地址
 * 小端字节序：最高有效为存储与最高内存地址，最低有效位存储与最低内存地址
 * 主机字节序：不同主机有不同的字节序，如x86为小端字节序
 * 网络字节序：网络字节序规定为大端字节序
 */
#include <stdio.h>
#include <arpa/inet.h>

int main(void) 
{
	unsigned int x = 0x12345678;
	unsigned char *p = (unsigned char*)&x;
	printf("%0x %0x %0x %0x\n", p[0], p[1], p[2], p[3]);

	unsigned int y = htonl(x);
	p = (unsigned char *)&y;
	printf("%0x %0x %0x %0x\n", p[0], p[1], p[2], p[3]);

	return 0;
}
