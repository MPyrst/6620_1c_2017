#include <stdio.h>
int main() {
	char buf[80];
	int cookie=1;
	printf("buf: %08x cookie: %08x\n", &buf, &cookie);
	gets(buf);
	printf ("cookie: %08x\n", cookie);
	if (cookie == 0x41424344)
		printf("you win!\n");
}
