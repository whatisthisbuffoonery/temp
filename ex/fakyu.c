#include <fcntl.h>
#include <unistd.h>

void ft_putstr_ext(int fd, char *v, char ext)
{
	int i = 0;
	while (v[i])
		i ++;
	write(fd, v, i - 1);
	write(fd, &ext, 1);
}

void ft_putstr(int fd, char *a)
{
	int i = 0;
	while (a[i])
		i ++;
	write(fd, a, i);
}

int main(int c, char **v)
{
	if (c < 2)
		return (1);
	int i = 1;
	int fd = open ("fuckoff.txt", O_CREAT | O_WRONLY, 0644);
	while (i < c)
	{
		ft_putstr_ext(fd, v[i], 'o');
		ft_putstr(fd, ": ");
		ft_putstr_ext(fd, v[i], 'c');
		ft_putstr(fd, "\n\t$(CC) $(CC_FLAGS) $< -o $@\n");
		i ++;
	}
	close(fd);
}
