#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int	main(void)
{
	char *a = malloc(1);

	int b = fork();
	a[0] = 'q';
	if (!b)
	{
		a[0] = 'o';
		usleep(8000000);
	}
	if (b)
	{
		usleep(4000000);
		kill(b, SIGTERM);
		free(a);
	}
}
