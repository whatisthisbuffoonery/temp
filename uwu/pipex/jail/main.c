#include "h_pipex.h"

static int	err(int n)
{
	if (n < 0)
		perror(strerror(errno));
	return (n);
}

static char	**cmd_cleanup(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
	return (NULL);
}
//close(-1) is safe
static void	file_cleanup(int *pfd, int *filefd)
{
	if (pfd[0] != filefd[0])
		close(pfd[0]);
	if (pfd[1] != filefd[1])
		close(pfd[1]);
	close(filefd[0]);
	close(filefd[1]);
}

static int	init(char **v, int *pfd, int *filefd)
{
	int	result;

	pfd[0] = -1;
	pfd[1] = -1;
	filefd[0] = err(open(v[1], O_RDONLY));
	filefd[1] = err(open(v[4], O_WRONLY));
	result = err(pipe(pfd));
	if (filefd[0] < 0 || filefd[1] < 0 || result)
	{
		file_cleanup(pfd, filefd);
//		perror(strerror(errno));
		return(1);
	}
	ft_putnbr_fd(pfd[0], 1);
	write(1, "\n", 1);
	ft_putnbr_fd(pfd[1], 1);
	write(1, "\n", 1);
	ft_putnbr_fd(filefd[0], 1);
	write(1, "\n", 1);
	ft_putnbr_fd(filefd[1], 1);
	write(1, "\n", 1);
	return (0);
}
//one pipe per command in minishell, here its forks that take from the same pipe- should I handle that in the child?

static char **prepend_cmd(char *v)
{
	int		len;
	char	**cmd;
	char	*ret;//have another stack string?

	cmd = ft_split(v, ' ');
	if (!cmd)
		return (NULL);
	len = ft_strlen(cmd[0]) + ft_strlen("/usr/sbin/");
	ret = malloc((len + 1) * sizeof(char));//fuck I have to check sbin too
	if (!ret)
		return (cmd_cleanup(cmd));
	ft_strlcpy(ret, "/usr/bin/", len);
	ft_strlcat(ret, cmd[0], len);
	if (access(ret, X_OK))
	{
		ft_strlcpy(ret, "/usr/sbin/", len);
		ft_strlcat(ret, cmd[0], len);
	}
	if (access(ret, X_OK))
		return ((free(ret)), cmd_cleanup(cmd));
	free(cmd[0]);
	cmd[0] = ret;
	return (cmd);
}

static void	fork_handle(char *v, int *pfd, int *filefd, int *cpid)//room for an unset fd func that sets fd pointer to -1
{
	int		fd_index;
	char	**cmd;

	fd_index = *cpid;
	*cpid = fork();
	if (*cpid)
		return ;
	cmd = prepend_cmd(v);
	if (!cmd || err(dup2(filefd[fd_index], pfd[fd_index])) < 0)
	{
		file_cleanup(pfd, filefd);
	}
	else
	{
		close(filefd[!fd_index]);
		execve(cmd[0], &cmd[0], NULL);
		perror(strerror(errno));
		ft_putstr_fd(cmd[0], 1);
		close(filefd[fd_index]);
		close(pfd[!fd_index]);
		close(pfd[fd_index]);//wtf spec
	}
	cmd_cleanup(cmd);
	exit(1);
}

int	wvalue(int cpid)
{
	int	n;

	waitpid(cpid, &n, 0);
	if (WIFEXITED(n))
		return (WEXITSTATUS(n));
	return (255);
}

//1, 4 = files, 2, 3 = cmd
int	main(int c, char **v)
{
	//prepend /usr/bin or /usr/sbin //make it a 1kb stack string
	int		pfd[2];
	int		filefd[2];
	pid_t	cpid[2];
	// also also the process need to link to each other, use dup_uno

	if (c != 5 || !v[1] || !v[2] || !v[3] || !v[4])//outsource here...
		return (1);
	cpid[0] = 0;
	cpid[1] = 1;
	if (!init(v, pfd, filefd))
	{
		fork_handle(v[2], pfd, filefd, &cpid[0]);
		if (!wvalue(cpid[0]))
			fork_handle(v[3], pfd, filefd, &cpid[1]);
	}
	file_cleanup(pfd, filefd);
	wait(NULL);
}
