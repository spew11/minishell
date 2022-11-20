#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
	char buf[256];
	getcwd(buf, 256);
	printf("%s\n", buf);
	if (chdir("/") < 0) {
		exit(1);
	}
	getcwd(buf, 256);
	printf("%s\n", buf);
	return 0;
}
