#include "h_pipex.h"

void	make_pipes(int c, char **v, t_pipelist *pl)//c and v inherited
{
	int	i;

	i = 0;
	pl->head = malloc((c - 3) * sizeof(t_pipe));
	if (!pl->head)
		return ;
	while (i < c - 3)//yet to do dup2 in init
	{
		if (pipe(ps->head[i].pfd))
			return (pipe_cleanup(pl, i));//allow -1 to mean max
		pl->head[i].v = v[i + 2];
		if (i + 1 < c - 3)
		ps->head[i].next = ps->head[i + 1];
		i ++;
	}
	pl->tail = ps->head[i - 1];
}
