#include "h_pipex.h"

//err msg indicator semantics to be confirmed

int	cmd_err(int n, char *str)//rewrite to have this func do ft find char, maybe include "pipex"
{
	char	*tmp;

	tmp = NULL;
	if (errno && str && errno != ENOENT)
		tmp = ft_strrchr(str, '/');
	if (tmp)
		str = tmp;
	if (n < 0)
		perror(str);//strrchr '/' if errno == enoent
	return (n);
}

int  err(int n, char *str)//rewrite to exclude pipex on occasion
{
	if (n < 0)
	{
		write(2, "pipex: ", 7);
		perror(str);
	}
	return (n);
}
//perror statements everywhere

void	unset(int *fd)
{
	if (*fd > 2)
		close(*fd);
	*fd = 0;
}
//confirm list of fall thru errno
void	fd_cleanup(int *pfd, int *ffd, char **v)//ffd cleanup in fork()//consider null pointer
{
	int	i;
	int	len;

	len = 0;
	while (v[len])
		len ++;
	len = 2 * ((len - (1 + 1)) - !ft_strcmp(v[1], "here_doc"));
	i = 0;
	while (i < len)
		unset(&pfd[i++]);
	i = 0;
	while (ffd && i < len)
	{
		if (*ffd == pfd[i])
			*ffd = -1;
		i ++;
	}
	unset(ffd);
	free(pfd);
}

int	cmd_cleanup(char ***cmd)
{
	int	i;

	i = 0;
	if (!*cmd)
		return (1);
	while ((*cmd)[i])
		free((*cmd)[i++]);
	free(*cmd);
	*cmd = NULL;//yes.
	return (-1);
}
