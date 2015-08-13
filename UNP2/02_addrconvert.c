#include <stdio.h>
#include <arpa/inet.h>

int main(void)
{
	//点分十进制IP地址转换成网络字节序地址
	unsigned long addr = inet_addr("192.168.0.1");
	printf("addr = %u\n", ntohl(addr));

	//地址结构转换成点分十进制IP地址
	struct in_addr ipaddr;
	ipaddr.s_addr = addr;
	printf("%s\n", inet_ntoa(ipaddr));

	return 0;
}
