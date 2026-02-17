#include "h_pipex.h"

int	std_dup(int *pfd, int *ffd, int i, char **v)
{
	int	fd;

	probe(pfd[0], "in");
	probe(pfd[3], "out");
	probe(i, "dup_i");
	fd = pfd[0];
	if (*ffd > 2 && i < 3 + !ft_strcmp(v[1], "here_doc"))
	{
		probe(*ffd, "!!!ffd_in!!!");
		fd = *ffd;
	}
	if (dup2(fd, 0) < 0)
		return (err(-1, "dup2 error"));//bash would not mention dup, consider NULL
	fd = pfd[3];
	if (*ffd > 2 && !v[i + 2])
	{
		probe(*ffd, "!!!ffd_out!!!");
		fd = *ffd;
	}
	if (dup2(fd, 1) < 0)
	{
		close(0);
		return (err(-1, "dup2 error"));
	}
	return (0);
}

int	ffd_init(char **v, int *i, int **pfd, int *ffd)
{
	errno = 0;
	if (*i == 1)
		*ffd = ffd_start(v, i);
	else if (!v[*i + 2])
		*ffd = ffd_end(v[*i + 1], !ft_strcmp(v[1], "here_doc"));//pass strcmp to another wrapper
	if (*ffd < 0)
	{
		if (errno == ENOENT)
			*i = 0;
		else
			*i = 1;
		fd_cleanup(pfd, ffd, v);
		return (1);
	}
	return (0);
}

int	pfd_grab(int i, char **v)
{
	int	heredoc;

	heredoc = !ft_strcmp(v[1], "here_doc");
	return (2 * (i - (1 + 1 + heredoc)));
}
//
//i value without heredoc: 2, 3, 4, 5, ...
//with: 3, 4, 5, 6, ...

void	print_pfd(int *pfd)
{
	ft_putnbr(pfd[0]);
	ft_putstr("\n");
	ft_putnbr(pfd[1]);
	ft_putstr("\n");
	ft_putnbr(pfd[2]);
	ft_putstr("\n");
	ft_putnbr(pfd[3]);
	ft_putstr("\n");
}

int	fork_handler(char **v, int *i, int *pfd_src, int *ffd)//offload ffd cleanup later
{
	pid_t	cpid;
	char	**cmd;
	int		*pfd;

	errno = 0;
	cpid = fork();
	if (cpid)
	{
		probe(*i, "i_start");
		if (*i == 1)//remove end file cond, adjust loop in main
			*i += 1;
		*i += 1;
		probe(*i, "i_ret");
		return (err(cpid, "fork"));//just "fork"
	}
//	probe(*i, "before: ");
	if (ffd_init(v, i, &pfd_src, ffd))
		exit(*i);
//	probe(*i, "after: ");
	probe(pfd_grab(*i, v), "pfd_index");
	pfd = &pfd_src[pfd_grab(*i, v)];
	print_pfd(pfd);
	if(cmd_init(v, i, &cmd) || std_dup(pfd, ffd, *i, v))
		child_err(cmd, v, &pfd_src, ffd);//set ffd to 0 if any match
	fd_cleanup(&pfd_src, ffd, v);
	execve(cmd[0], cmd, NULL);//pfd cleanup first
	cmd_err(-1, cmd[0]);//strrchr '/'
	close(0);
	close(1);
	child_err(cmd, NULL, NULL, NULL);
	return (cpid);
}//fuck I have to do a separate loop for waitpid
