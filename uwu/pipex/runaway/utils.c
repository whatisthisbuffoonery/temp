#include "h_pipex.h"

//err msg indicator semantics to be confirmed

void	probe(int n, char *a)
{
	ft_putstr(a);
	ft_putstr(": ");
	ft_putnbr(n);
	write(1, "\n", 1);
}

int	cmd_err(int n, char *str)//rewrite to have this func do ft find char, maybe include "pipex"
{
	char	*tmp;

	tmp = NULL;
	if (errno && str && errno != ENOENT)
		tmp = ft_strrchr(str, '/');
	if (tmp)
		str = tmp;
	if (n < 0)
	{
		ft_putstr("cmd: ");
		perror(str);//strrchr '/' if errno == enoent
	}
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
void	fd_cleanup(int **pfd_src, int *ffd, char **v)//ffd cleanup in fork()//consider null pointer
{
	int	i;
	int	len;
	int	*pfd;

	pfd = *pfd_src;
	if (!pfd)
		return ;
	len = pfd_len(v);
	i = 0;
//	probe(len, "len");
	while (i < len)
		unset(&pfd[i++]);
//	probe(i, "i");
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
	if (!*cmd)
		return (1);
	while ((*cmd)[i])
		free((*cmd)[i++]);
	free(*cmd);
	*cmd = NULL;//yes.
	return (-1);
}
