#include "libft.h"

int main(int c, char **v)
{
	int	i;
	int	val;

	if (c < 2)
		return (1);
	i = 1;
	val = 0;
	while (v[i])
	{
		val ^= ft_atoi(v[i]);
		i ++;
	}
	ft_putnbr(val);
	write(1, "\n", 1);
}
