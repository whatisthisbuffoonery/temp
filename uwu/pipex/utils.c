#include "h_pipex.h"

int	cmd_err(int n, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (errno && str && errno != ENOENT)
		tmp = ft_strrchr(str, '/');
	if (tmp)
		str = tmp;
	if (n < 0)
		perror(str);
	return (n);
}

int	err(int n, char *str)
{
	if (n < 0)
	{
		write(2, "pipex: ", 7);
		perror(str);
	}
	return (n);
}

void	unset(int *fd)
{
	if (*fd > 2)
		close(*fd);
	*fd = 0;
}

void	fd_cleanup(int **pfd_src, int *ffd, char **v)
{
	int	i;
	int	len;
	int	*pfd;

	pfd = *pfd_src;
	if (!pfd)
		return ;
	len = pfd_len(v);
	i = 0;
	while (i < len)
		unset(&pfd[i++]);
	i = 0;
	while (ffd && *ffd > 2 && i < len)
	{
		if (*ffd == pfd[i])
			*ffd = -1;
		i ++;
	}
	if (ffd)
		unset(ffd);
	free(pfd);
	*pfd_src = NULL;
}

int	cmd_cleanup(char ***cmd)
{
	int	i;

	i = 0;
	if (*cmd)
	{
		while ((*cmd)[i])
			free((*cmd)[i++]);
		free(*cmd);
		*cmd = NULL;
	}
	return (1);
}
