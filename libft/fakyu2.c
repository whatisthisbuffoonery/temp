#include <unistd.h>
#include <fcntl.h>

void ft_putstr(int fd, char *v)
{
	int i = 0;
	while (v[i])
		i ++;
	write(fd, v, i);
}

void ft_putstr_ext(int fd, char *v)
{
	int i = 0;
	while (v[i])
		i ++;
	write(fd, v, i - 1);
	write(fd, "o", 1);
}

int main(int c, char **v)
{
	if (c < 2)
		return (1);
	int i = 1;
	int fd = open("fuckoff2.txt", O_CREAT | O_WRONLY, 0644);
	write(fd, "dot_o := ", 7);
	while (i < c)
	{
		ft_putstr_ext(fd, v[i]);
		if (!(i % 5))
			ft_putstr(fd, "\n");
		else
			ft_putstr(fd, " ");
		i ++;
	}
}
