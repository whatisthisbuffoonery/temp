#include "h_pipex.h"

int	std_dup(int ffd, int i)
{
	int	std;

	if (!ffd)
		return (0);
	std = 1;
	if (i == 1)
		std = 0;
	if (dup2(ffd, std))
		return (1);
	return (0);
}

int	fork_handler(char **cmd, int *pfd, int *i, int *ffd)//offload ffd cleanup later
{
	int	cpid;
 
	cpid = fork();
	if (!cpid)
	{
		if (std_dup(*ffd, *i))
			break ;
		execve(cmd[0], cmd, NULL);
		close(0);
		close(1);
	}
	if (*ffd > 0)
		close(*ffd);
	*ffd = 0;
	return (cpid);
}
