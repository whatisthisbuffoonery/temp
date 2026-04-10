#ifndef H_MINISHELL_H
# define H_MINISHELL_H

# include <signal.h>
# include <stdio.h>//readline
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

typedef struct s_cmd
{
	struct s_cmd	*next;
	char			*str;//stored one word or quoted section
	char			type;//stores just first char of pre parsed string, which might be a dquote excluded from str field
	//other linked list todo
}					t_cmd;

#endif
//global var thing
