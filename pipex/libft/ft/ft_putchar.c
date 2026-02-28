#include <unistd.h>

void	ft_putchar(char n)
{
	write(1, &n, 1);
}
