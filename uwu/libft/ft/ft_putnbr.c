#include <unistd.h>

void	ft_putnbr(int src)
{
	unsigned int	n;
	unsigned int	t;
	char			a;

	n = src;
	t = 1;
	if (src < 0)
	{
		write(1, "-", 1);
		n = 0 - ((unsigned int) src);
	}
	while (n / t > 9)
		t *= 10;
	while (t)
	{
		a = ((n / t) % 10) + '0';
		write(1, &a, 1);
		t /= 10;
	}
}
