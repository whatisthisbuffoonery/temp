#ifndef H_MINISHELL_H
# define H_MINISHELL_H

# include <signal.h>
# include <stdio.h>//
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"

typedef struct s_handler
{
	struct sigaction	mini;
	struct sigaction	old;
}						t_handler;

#endif
//global var thing
