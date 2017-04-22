#include <stdio.h>
void stack5(){
	char buf[80];
	int cookie;
	printf("buf: %08x cookie: %08x\n", &buf, &cookie);
	gets(buf);
	printf("Cookie: %08x\n",cookie);
	if (cookie == 0x000d0a00)
		printf("you lose!\n");
}
