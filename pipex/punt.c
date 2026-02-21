#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

void	ft_putstr(char *a)
{
	int i = 0;

	while (a[i])
		i ++;
	write(1, a, i);
}

int main(int c, char **v)
{
	if (c < 2)
		return (1);
	ft_putstr(v[1]);
	write(1, "\n", 1);
	errno = ENOENT;
	perror(NULL);
}
