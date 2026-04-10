#include <unistd.h>

int main(int c, char **v, char **e)
{
	char *a[3];

	a[0] = "/usr/bin/echo";
	a[1] = "$a";
	a[2] = NULL;
	(void) c;
	(void) v;
	execve(a[0], a, e);
}
