#include "h_pipex.h"

int	edge_init(t_pipelist **pl, int *filefd, char *f1, char *f2)//herdoc condition here
{
	if (!strcmp(f1, "heredoc"))
		filefd[0] = 0;
	else
		filefd[0] = open(f1, O_RDONLY);
	if (filefd[0] < 0)
		return (1);
	filefd[1] = open(f2, O_WRONLY);
	if (filefd[1] < 0)
	{
		if (filefd[0] > 0)
			close(filefd[0]);
		return (1);
	}
	return (0);
}

int	valid(int c, char **v)
{
	int	i;

	i = 1;
	while (i < c)
	{
		if (i != 1 && !strcmp(v[i], "heredoc"))
			return (0);
		i ++;
	}
	return (1);
}

//scaling this for minishell is gonna involve making a cmd struct with:
//dedicated fd fields (different pipes)
//heredoc indicator (to imitate bash, we are using carrots now)
// cat file | cat file later overrides pipe setup, thankfully we have pipe symbols now
int	main(int c, char **v)
{
	t_pipelist	*pl;
	int			filefd[2];

	if (c != 5 || !valid(c, v))
		return (1);
	pl = malloc(sizeof(t_pipelist));
	if (!pl)
		return (1);
	if (edge_init(filefd, v[1], v[c - 1]))
	{
		free(pl);
		return (1);
	}
	if (!make_pipes(c, pl, filefd))
		fork_handler(v + 2, pl);//return here on failure
	pipe_cleanup(pl);
	free(pl);
	close(filefd[1]);
	if (filefd[0] > 0)
		close(filefd[0]);
	return (1);
}
