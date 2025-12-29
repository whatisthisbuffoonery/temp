#include <unistd.h>
#include <stdlib.h>

int main(void)
{
//	char *v[] = {"/usr/bin/echo", "a", NULL};
//	char *e[] = {NULL};
//	write(1, "content\n", 8);
	write(1, "a", 1);
//	execve("/usr/bin/echo", v, e);
}
