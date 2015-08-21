#include "../unp.h"

int
gethostaddr(char *addr)
{
	char hostname[100] = {0};
	if (gethostname(hostname, sizeof(hostname)) < 0)
		return -1;

	struct hostent *ht;
	if ((ht = gethostbyname(hostname)) == NULL)
		return -1;

	strcpy(addr, inet_ntoa(*(struct in_addr*)ht->h_addr));
	return 0;
}
