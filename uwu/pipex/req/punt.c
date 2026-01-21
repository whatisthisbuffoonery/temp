#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(void)
{
	char *v[] = {"/usr/bin/echo", "-lala", NULL};
	char *e[] = {NULL};
//	write(1, "content\n", 8);
	execve("/usr/bin/echo", v, e);
	perror(strerror(errno));
}
