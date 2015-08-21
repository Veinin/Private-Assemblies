#include "../unp.h"

#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>

int
main(void)
{
	//gethostname 获取主机名
	char hostname[100] = {0};
	gethostname(hostname, sizeof(hostname));
	printf("hostname : %s\n", hostname);

	//gethostbyname 根据主机名获取地址信息
	struct hostent *ht;
	if ((ht = gethostbyname(hostname)) == NULL)
		ERR_EXIT("gethostbyname");
	
	int i = 0;
	while (ht->h_addr_list[i] != NULL)
	{
		printf("addr : %s\n", inet_ntoa(*(struct in_addr*)ht->h_addr_list[i]));
		i++;
	}

	//gethostaddr
	char addr[16] = {0};
	if(gethostaddr(addr) < 0)
		ERR_EXIT("gethostaddr");
	printf("local host addr : %s\n", addr);

	return 0;
}
