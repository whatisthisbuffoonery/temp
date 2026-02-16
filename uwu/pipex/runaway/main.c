#include "h_pipex.h"

//swapping out pfd is very painful, we are coding for async stuff. dont close()?

int	pfd_len(char **v)
{
	int	i;

	i = 0;
	while (v[i])
		i ++;
	return ((i - 1) * 2);
}

int	pfd_init(char **v, int **pfd)
{
	int	len;
	int	i;


	len = pfd_len(v);//wrap strcmp for bonus
//	probe(len, "malloc");
	*pfd = malloc(len * sizeof(int));
	if (!*pfd)
		return (err(-1, "malloc error"));
	i = 0;
	while (i < len)
		(*pfd)[i++] = 0;
	i = 0;
	while (i < len)
	{
		if (err(pipe(&(*pfd)[i]), "pipe error"))
		{
			fd_cleanup(pfd, NULL, v);
			return (1);
		}
		i += 2;
	}
	return (0);
}

int	main_init(int **pfd, int *i, int c, char **v)
{
	*i = 1;
	if (pipex_arg(c))
		*i = 127;
	else if (!pfd_init(v, pfd))
		return (0);
	return (1);
}

int	waiter(void)
{
	int	ret;
	int	tmp;

	ret = child_wait();
	tmp = child_wait();
	while (tmp >= 0)
	{
		ret = tmp;
		tmp = child_wait();
	}
	return (ret);
}

//exit code is a race cond make a malloc array of cpids and use waitpid
//or close the first pipe end and waitpid one at a time

int	main_wait(int *pfd, int i, char **v)
{
	int	index;

	index = pfd_grab(i - 1, v);
	unset(&pfd[index]);
//	unset(&pfd[index + 1]);
	return (child_wait());
}

int	main(int c, char **v)
{
	int		i;
	int		n;
	int		ffd;
	int		*pfd;
	pid_t	cpid;

	ft_putstr("test: ");
	ft_putstr(v[0]);
	ft_putstr("\n");
	n = 0;
	if (main_init(&pfd, &i, c, v))//bonus diff, pass c
		return (i);
	while (i < c - 1)//for basic pipe, c == 5 and last file == 4
	{
		ffd = 0;
		if (!ffd_heredoc(v, &i, &ffd, pfd))
			cpid = fork_handler(v, &i, pfd, &ffd);
		else
			cpid = -1;
		if (cpid < 1)
			break;
		n = main_wait(pfd, i, v);
	}
	fd_cleanup(&pfd, &ffd, v);
	return (n);
}

/*
int	main(int c, char **v)
{
	int *pfd;
	int	len;

	if (c != 5)
		return (1);
	len = pfd_len(v);
	pfd = malloc(len * sizeof(int));
	probe(len, "len");
	pipe(pfd);
	pipe(&pfd[2]);
	pipe(&pfd[4]);
	pipe(&pfd[6]);
	fd_cleanup(&pfd, NULL, v);
	ft_putstr(v[2]);
	char **cmd = ft_split(v[2], ' ');
	ft_putnbr(ft_strlen(cmd[0]));
	cmd_cleanup(&cmd);
}
*/
