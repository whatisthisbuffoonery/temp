#include "get_next_line.h"
/*
static int muh_putnbr(int n)
{
	char a;
	int t = 1;
	if (n < 0)
	{
		write(1, "-", 1);
		n = 0 - n;
	}
	while (n / t > 9)
		t *= 10;
	while (t)
	{
		a = ((n / t) % 10) + '0';
	}
}
*/
static int muh_atoi(char *v)
{
	int i = 0;
	int a = 0;
	while (v[i])
	{
		a *= 10;
		a += v[i] - '0';
		i ++;
	}
	if (!a)
		write(1, "wtf\n", 4);
	return (a);
}

int main(int c, char **v)
{
	if (c < 3)
		return (1);
	int fd = open(v[1], O_RDONLY);
	if (fd < 0)
		return ((write(1, "no open\n", 8)), 1);
	int line = muh_atoi(v[2]);
	char *receive = NULL;
	while (line)
	{
		receive = get_next_line(fd);
		if (receive == NULL)
			return ((write(1, "how\n", 4)), (close(fd)), 1);
		line --;
		if (!line)
			break ;
		free(receive);
	}
	int i = 0;
	while (receive[i])
		i ++;
	write(1, receive, i);
	free(receive);
	close(fd);
}
