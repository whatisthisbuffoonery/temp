#include "h_pipex.h"

void	child_wait(int cpid)
{
	int		n;
	pid_t	w_return;

	errno = 0;
	w_return = waitpid(cpid, &n, 0);
	while (errno == EINTR && w_return < 0)
		w_return = waitpid(cpid, &n, 0);
	//no waitpid error msg nor stop logic //n?
}

void	child_err(char **cmd, char **v, int *pfd, int *ffd)
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