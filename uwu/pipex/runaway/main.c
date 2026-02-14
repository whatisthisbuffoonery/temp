#include "h_pipex.h"

//swapping out pfd is very painful, we are coding for async stuff. dont close()?

int	pfd_init(int c, char **v, int **pfd)
{
	int	len;
	int	i;


	len = 2 * ((c - (1 + 1)) - !ft_strcmp(v[1], "here_doc"));//wrap strcmp for bonus
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
			return (fd_cleanup(pfd, c, NULL));
		i += 2;
	}
}

int	main_init(int **pfd, int *i, int c, char **v)
{
	*i = 1;
	if (pipex_arg(c))
		*i = 127;
	else if (!pfd_init(c, v, pfd))
		return (0);
	return (1);
}

int	main(int c, char **v)
{
	int		i;
	int		ffd;
	int		*pfd;
	pid_t	cpid;

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
		child_wait(cpid);
	}
	fd_cleanup(pfd, &ffd, v);
	return ((cpid < 0));
}
