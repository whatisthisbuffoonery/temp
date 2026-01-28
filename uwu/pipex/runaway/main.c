#include "h_pipex.h"


//swapping out pfd is very painful, we are coding for async stuff. dont close()?
void	pfd_cycle(int *pfd)
{
	int	tmp[2];

	tmp[0] = pfd[0];
	tmp[1] = pfd[1];
	pfd[0] = pfd[2];
	pfd[1] = pfd[3];
	pfd[2] = tmp[0];
	pfd[3] = tmp[1];
}

int	pipe_init(int *pfd)
{
	if (pipe(pfd))
		return (1);
	if (pipe(pfd + 2))
	{
		close(pfd[0]);
		close(pfd[1]);
		return (1);
	}
	pfd[0] = -1;
	pfd[1] = -1;
	pfd[2] = -1;
	pfd[3] = -1;
	return (0);
}

int	main(int c, char **v)
{
	int		i;
	int		ffd;
	int		pfd[4];
	pid_t	cpid;
	char	**cmd;

	if (c < 5 || pipe_init(pfd))//bonus diff
		return (err(0 - (c >= 5)));
	i = 1;
	cmd = NULL;
	ffd = 0;
	while (i < c - 1)
	{
		cpid = -1;
		if (!cmd_init(v, &i, &cmd, &ffd))//file open here
			cpid = fork_handler(cmd, pfd, &i, &ffd);//file close here, reset to 0 //if i == 1 else if ffd > 0
		else//we are dunking fork() with the cleanup funcs, do space for control flow here
			break ;
		pfd_cycle(pfd);
		cmd_cleanup(&cmd);//pass ptr and set to null
		if (wvalue(cpid) < 1)
			break ;
	}
	fd_cleanup(pfd);
}
