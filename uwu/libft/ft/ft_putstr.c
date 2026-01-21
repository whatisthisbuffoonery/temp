#include "libft.h"

//make a nullable version

void	ft_putstr(char *a)
{
	int	i;

	i = 0;
	while (a[i])
		i ++;
	write(1, a, i);
}
