#include "h_pipex.h"

int	cmd_init(t_pipelist *pl, int c, char **v)
{
	int	i;
	int	k;

	i = 2;
	k = 0;
	while (i < c)
	{
		if (!strcmp(v[i], "here_doc"))
		{
			pl->arr[k].heredoc_flag = 1;
			i += 2;
		}
		if (i >= c)
			return (1);
		pl->arr[k++].v_index = i++;
	}
}
