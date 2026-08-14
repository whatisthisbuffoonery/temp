#include <unistd.h>
#include <sys/stat.h>
#include <strings.h>

void	ft_putstr(char *s)
{
	int	i = 0;

	while (s[i])
		i ++;
	write(1, s, i);
	write(1, "\n", 1);
}

int	ext_check(char *v)
{
	int	i = 0;

	while (v[i])
		i ++;
	if (i < 5
		|| v[--i] != 'p'
		|| v[--i] != 'p'
		|| v[--i] != 'c'
		|| v[--i] != '.')
		return (1);
	return (0);
}

int	main(int c, char **v, char **e)
{
	struct stat	statbuf;
	char	*argv[7];

	bzero(&statbuf, sizeof(struct stat));
	if (c != 2)
		ft_putstr("pass in ONE arg");
	else if (stat(v[1], &statbuf))
		ft_putstr("aint see file");
	else if (!S_ISREG(statbuf.st_mode) || ext_check(v[1]))
		ft_putstr("wtf did you pass in");
	else
	{
		argv[0] = "/usr/bin/c++";
		argv[1] = "-Wall";
		argv[2] = "-Wextra";
		argv[3] = "-Werror";
		argv[4] = "-std=c++98";
		argv[5] = v[1];
		argv[6] = NULL;
		return (execve(*argv, argv, e));
	}
	return (1);
}
