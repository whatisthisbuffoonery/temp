#include <unistd.h>

void	ft_putstr(char *a)
{
	int i = 0;
	while (a[i])
		i ++;
	write(1, a, i);
	write(1, "\n", 1);
}

int main(int c, char **v)
{
	if (c < 2)
		return (1);
	ft_putstr(v[1]);
}
