#include "minitalk.h"

void	server(int sig)
{
	static char	table[

int	main(void)
{
	signal(SIGUSR1, server);
	signal(SIGUSR2, server);
	while (1)
	{
		pause();
	}
}
