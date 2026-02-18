#include "h_pipex.h"

int	pfd_len(char **v)
{
	int	i;

	i = 0;
	while (v[i])
		i ++;
	return ((i - (1 + heredoc_cond(v))) * 2);
}

int	pfd_init(char **v, int **pfd)
{
	int	len;
	int	i;

	len = pfd_len(v);
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
		*i = 0;
	else if (!pfd_init(v, pfd))
		return (0);
	return (1);
}

int	main_wait(int *pfd, int i, char **v)
{
	int	index;

	i --;
	index = pfd_grab(i, v);
	unset(&pfd[index + 1]);
	return (child_wait());
}

//for basic pipe, c == 5 and last file == 4

int	main(int c, char **v)
{
	int		i;
	int		n;
	int		ffd;
	int		*pfd;
	pid_t	cpid;

	n = 0;
	if (main_init(&pfd, &i, c, v))
		return (i);
	while (i < c - 1)
	{
		ffd = 0;
		if (!ffd_heredoc(v, &i, &ffd, pfd))
			cpid = fork_handler(v, &i, pfd, &ffd);
		else
			cpid = -1;
		if (cpid < 1)
			break ;
		n = main_wait(pfd, i, v);
	}
	fd_cleanup(&pfd, &ffd, v);
	return (n);
}
