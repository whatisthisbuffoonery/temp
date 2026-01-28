#include "h_pipex.h"

//err msg indicator semantics to be confirmed
int  err(int n)
{
	if (n < 0)
		perror(strerror(errno));
	return (n);
}

int	wvalue(int cpid)
{
	int		n;
	pid_t	w_return;

	if (cpid < 1)
		return (err(cpid));
	errno = 0;
	w_return = waitpid(cpid, &n, 0);//reset errno here? hm
	while (errno == EINTR && w_return < 0)
	{
		errno = 0;
		w_return = waitpid(cpid, &n, 0);
	}
	if (w_return < 0)
		return (err(w_return));
	else if (WIFEXITED(n))
		return (err(WEXITSTATUS(n)));
	return (255);
}

void	fd_cleanup(int *pfd)
{
	close(pfd[0]);
	close(pfd[1]);
	close(pfd[2]);
	close(pfd[3]);
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
	*cmd = NULL;
}
