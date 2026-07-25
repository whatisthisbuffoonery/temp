#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int	main(void)
{
	char *a = malloc(1);

	int b = fork();
	a[0] = 'q';
	if (b)
		kill(b, SIGTERM);
	free(a);
}
