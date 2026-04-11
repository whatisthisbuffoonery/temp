#ifndef H_MINISHELL_H
# define H_MINISHELL_H

# include <signal.h>
# include <stdio.h>//readline
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"

//didnt use
typedef struct s_handler
{
	struct sigaction	mini;
	struct sigaction	old;
}						t_handler;

typedef struct s_shnode
{
	char			*name;
	char			*str;
	struct s_shnode	*next;
}					t_shnode;

typedef struct s_cmd
{
	struct s_cmd	*next;
	char			*str;//stores one word or quoted section
	t_shnode		*env;//expansion list
	char			type;//stores just first char of pre parsed string, which might be a dquote excluded from str field
}					t_cmd;

//t_list? //t_shnode? (just has str field) //self reallocing char **?
typedef struct	s_env
{
	t_shnode	*export;
	t_shnode	*env;
}				t_env;

//didnt use
typedef struct	s_minishell
{
	t_cmd	*cmd;
	t_env	*env;
}			t_minishell;
#endif
//global var thing
