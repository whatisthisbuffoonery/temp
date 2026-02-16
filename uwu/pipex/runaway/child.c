#include "h_pipex.h"

int	child_wait(void)
{
	int		n;
	pid_t	w_return;

	errno = 0;
	w_return = wait(&n);
	while (errno == EINTR && w_return < 0)
		w_return = wait(&n);
	if (w_return >= 0)
		return (WEXITSTATUS(n));
	return (w_return);
	//no waitpid error msg nor stop logic //n?
}

void	child_err(char **cmd, char **v, int **pfd, int *ffd)
{
    if (pfd)
	    fd_cleanup(pfd, ffd, v);
	cmd_cleanup(&cmd);
	if (errno == EACCES || errno == ENOEXEC)
		exit(126);
	if (errno == ENOENT)
		exit(127);
	exit(1);
}
