#include "h_pipex.h"

//elect for FD_CLOEXEC, wont change pipex i think
//cmd1 uses pipe0 which has [file, ususedfd], uses pipe1's write end
//cmd2 uses pipe1's read end and pipe2's write end
void	pipex_exec(t_pipelist *pl, int i, char **cmd)
{
	int	flag;

	flag = 0;
	if (dup2(pl->arr[i].pfd[0], 0))
		flag = 1;
	if (!flag && dup2(pl->arr[i + 1].pfd[1], 1))
	{
		close(0);
		flag = 1;
	}
	if (!flag)
		execve(cmd[0], cmd, NULL);
}

int new_pipe(t_pipelist *pl, int i)
{
	if (pipe(pl->arr[i].pfd))
		return (1);
	pl->top += 1;
	return (0);
}

int	pipe_cleanup(t_pipelist *pl)
{
	int	i;

	i = 0;
	while (i >= pl->top)
	{
		close(pl->arr[i].pfd[0]);
		close(pl->arr[i].pfd[1]);
		i ++;
	}
	free(pl->arr);
	return (1);
}
//file cmd pipe cmd pipe cmd file // c = 6, args 5, args w/ pipes 7, pipes = c - 2 = 4 (2files, 2pipes)
//c - 2, v inherited, later v + 2 to sync
//malloc pl elsewhere
int	make_pipes(int c, t_pipelist *pl, int *filefd)
{
	int	i;

	i = 0;
	pl->top = -1;
	c -= 2;
	pl->arr = malloc(c * sizeof(t_pipe));
	if (!pl->arr)
		return (1);
	while (i < c)
	{
		if (new_pipe(pl, i))
			return (pipe_cleanup(pl));
		i ++;
	}
	if (dup2(filefd[0], pl->arr[0].pfd[0])
		|| dup2(filefd[1], pl->arr[pl->top].pfd[1]))
		return (pipe_cleanup(pl));
	close(filefd[0]);//handle in caller
	close(filefd[1]);
	return (0);
}
