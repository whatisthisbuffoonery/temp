#include "h_minishell.h"

int	check_exit(int n)
{
	if (WIFEXITED(n))
		return (WEXITSTATUS(n));
	else if (WIFSIGNALED(n))
		return (WTERMSIG(n));
	return (-1);
}

int	child_wait(pid_t cpid)
{
	int		n;
	pid_t	w_return;

	errno = 0;
	w_return = waitpid(cpid, &n, 0);
	while (errno == EINTR && w_return < 0)
		w_return = waitpid(cpid, &n, 0);
	if (w_return >= 0)
		return (WEXITSTATUS(n));
	return (w_return);
}
