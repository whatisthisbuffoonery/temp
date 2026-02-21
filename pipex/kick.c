#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char *a = malloc(1);
	if (!fork())
	{
		sleep(1);
		exit(1);
	}
	free(a);
	exit (0);
}
