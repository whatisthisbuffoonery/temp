#include "h_pipex.h"

//1, 4 = files, 2, 3 = cmd

static void	cleanup(void)
{
	close(0);
	close(1);
}

int	file

int	err_help(char **v, int *fd_in, int *fd_out)//phase out in favor of file specific func
{
	int	in;
	int	out;

	if (access(v[2], F_OK) || access(v[3], F_OK))
		return (1);
	old_fd[0] = open(v[1], O_RDONLY);
	old_fd[1] = open(v[4], O_WRONLY);
	in = dup2(old_fd[0], 0);
	out = dup2(old_fd[1], 1);
	if (in < 0 || out < 0)
	{
		if (old_fd[0] >= 0 && in >= 0)
			close(0);
		else if (old_fd[0] >= 0)
			close(0);
		if (old_fd[1] >= 0 && out >= 0)
			close(1);
		else if (old_fd[1] >= 0)
			close(1);
		return (1);
	}
	return (0);
}

int	main(int c, char **v)
{
	char	*cmd[2];//prepend /usr/bin or /usr/sbin
	int		fd_in[2];
	int		fd_out[2];
	// also also the process need to link to each other, use dup_uno

	cmd[0] = NULL;
	cmd[1] = NULL;
	fd_in[1] = 1;//use standard stdin and stdout between processes, fd_in process writes to fd_out process
	fd_out[0] = 0;
	if (c != 5 || !v[1] || !v[2] || !v[3] || !v[4])
		return (1);
	if (cmd_help(v, cmd) || file_help(v, fd_in, fd_out))//i have to preprocess v to remove args, seperated by whitespace
		return (1);
}
