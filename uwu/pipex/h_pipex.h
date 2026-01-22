#ifndef H_PIPEX_H
# define H_PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include "libft.h"
# include <sys/wait.h>
# include <errno.h>

typedef struct s_pipe
{
	char			*v;
	int				pfd[2];
}					t_pipe;

typedef struct s_pipelist
{
	int		top;
	t_pipe	*arr;
}			t_pipelist;

#endif
