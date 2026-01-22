#include "h_pipex.h"

int	std_dup(int *fd)
{
	if (dup2(fd[0], 0))
		return (1);
	if (dup2(fd[1], 1))
	{
		if (fd[0] > 0)
			close(0);
		return (1);
	}
	return (0);
}

void	fork_handler(char **v, t_pipelist *pl)
{
	int		fd[2];
	int		flag;
	char	**cmd;

	if (err(fork()))
		return ;
	fd[0] = pl->arr[i].pfd[0];
	fd[1] = pl->arr[i + 1].pfd[1];
	flag = strcmp(v[0], "heredoc");//I have to make the heredoc file in /tmp and parse myself urrhhhhhgggg
	if (!flag)
		cmd = ft_split(v[i + 1]);
	else
		cmd = ft_split(v[i]);
	if (!cmd || std_dup(fd))
		return (cmd_cleanup(cmd));
	if (!flag)
	{

