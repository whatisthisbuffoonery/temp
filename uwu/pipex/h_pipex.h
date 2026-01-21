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
	struct s_pipe	*next;
	char			*v;
	int				pfd[2];
}					t_pipe;

typedef struct s_pipelist
{
	t_pipe	*head;
	t_pipe	*tail;
}			t_pipelist;

#endif
