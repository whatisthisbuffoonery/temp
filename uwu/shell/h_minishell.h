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
	struct sigaction	old;	//execve resets signal handlers for us, don't use. //although, signal masks will persist into execve. //I have to go dig up the online source for this
}						t_handler;

typedef struct s_shnode
{
	struct s_shnode	*next;
	char			*name;
	char			*str;
}					t_shnode;

typedef struct s_cmd
{
	struct s_cmd	*next;
	t_shnode		*env;		//expansion list //assert that operators are never assigned this list
	char			*str;		//stores one word, operator, or quoted section
	char			type;		//stores just first char of pre parsed string, which might be a dquote excluded from str field
	char			end_space;	//bool for whether the char after the token was whitespace
}					t_cmd;

//t_list? //t_shnode? (just has str field) //self reallocing char **?
typedef struct	s_env
{
	t_shnode	*export;		//env vars corresponding to export builtin	//export list stores env variables in no particular order, but can contain items with empty strings
	t_shnode	*env;			//env vars corresponding to env builtin		//env list stores env variables in alphabet order, items with empty strings as values are never added to this list
}				t_env;			//PSA empty strings can be in env list, null strings cannot

//didnt use
typedef struct	s_minishell
{
	t_cmd	*cmd;
	t_env	*env;
}			t_minishell;
#endif
//global var thing
