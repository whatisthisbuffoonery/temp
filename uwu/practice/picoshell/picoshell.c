#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>

#include <stdio.h>

typedef int	pfd[2];

void	pipe_clean(pfd *p, int lim)
{
	int	i = 0;

	printf("close: ");
	while (i <= lim)
	{
		close(p[i][0]);
		close(p[i][1]);
		printf("[%d, %d] ", p[i][0], p[i][1]);
		i ++;
	}
	printf("\n");
	free(p);
}

int	fd_setup(pfd *p, int i, int lim, char **v)
{
	int	fd[2] = {0, 1};

	if (i)
		fd[0] = p[i - 1][0];
	if (i <= lim)
		fd[1] = p[i][1];
	printf("fd: [%d, %d {%s}]\n", fd[0], fd[1], *v);
	int ret = (dup2(fd[0], 0) >= 0 && dup2(fd[1], 1) >= 1);
	pipe_clean(p, lim);
	return (!ret);
}

pid_t	picofork(char **argv, pfd *p, int i, int lim)
{
	pid_t	pid = fork();

	if (pid)
		return (pid);
	else if (!fd_setup(p, i, lim, argv))
	{
//		printf("run attempt: %s\n", *argv);
		execvp(*argv, argv);//no PATH insertion
	}
	exit(1);
}

int	pfd_init(pfd **dst, int *lim, char ***cmds)
{
	int	i = 0;

	while (cmds && cmds[i])
		i ++;
	if (i < 1)
		return (cmds != NULL);
	i -= 1;
	*dst = malloc(sizeof(pfd) * i);
	if (!*dst)
		return (1);
	*lim = i - 1;
	printf("pfd init: %d sets\n", i);
	i = 0;
	while (i <= *lim)
	{
		if (pipe((*dst)[i]))
		{
			pipe_clean(*dst, i - 1);
			return (1);
		}
		printf("[%d, %d] ", (*dst)[i][0], (*dst)[i][1]);
		i ++;
	}
	printf("\npfd init finished\n");
	return (0);
}

// char ***cmds for all I care
int	picoshell(char **cmds[])
{
	int	i = 0;
	int	lim;
	pfd	*p;
	pid_t	pid;

	if (pfd_init(&p, &lim, cmds))
		return (1);//no case for null cmds
	printf("limits [%d, %d]\n", i, lim);
	while (i <= lim + 1)
	{
		pid = picofork(cmds[i], p, i, lim);
		if (pid < 0)
			break ;
		i ++;
	}
	pipe_clean(p, lim);
	while (!(wait(NULL) < 0 && errno != EINTR))
		continue ;
	return (pid < 0);
}
