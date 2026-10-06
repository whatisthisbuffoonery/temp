#include <unistd.h>

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(int *dst, char *v)
{
	int	i = 0;
	int	a = 0;

	while (v[i])
	{
		if (!ft_isdigit(v[i]))
			return (1);
		a = (a * 10) + (v[i] - '0');
		i ++;
	}
	*dst = a;
	return (0);
}

//7, 2
//'7' - 2 = 5, 7 - 5 = 2
//'2' - 2 = 0, 7 - 0 = 7
int	sim(int s1, int s2, int n)
{
	int	a = n - s2;
	int	b = s1 - a;
	return (b);
}

void	ft_putnbr(int src)
{
	unsigned int	n = src;
	unsigned int	t = 1;
	char			a;

	if (src < 0)
	{
		n = 0u - n;
		write(1, "-", 1);
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

int	setup(int *s1, int *s2, char **v)
{
	if (ft_atoi(s1, v[1]) || ft_atoi(s2, v[2])) 
		return ((write(1, "improper args\n", 14)), 1);
	if (*s1 < *s2)
	{
		int	tmp = *s1;
		*s1 = *s2;
		*s2 = tmp;
	}
	write(1, "sim: ", 5);
	ft_putnbr(*s1);
	write(1, ", ", 2);
	ft_putnbr(*s2);
	write(1, "\n", 1);
	return (0);
}

int	main(int c, char **v)
{
	int	s1, s2;

	if (c != 3 || setup(&s1, &s2, v))
		return (1);
	write(1, "results: ", 8);
	ft_putnbr(sim(s1, s2, s1));
	write(1, ", ", 2);
	ft_putnbr(sim(s1, s2, s2));
	write(1, "\n", 1);
}
