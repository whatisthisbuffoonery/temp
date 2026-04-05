#include "h_minishell.h"

void	signal_init(void)
{
	sigset_t			mask;
	struct sigaction	hands;

	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	rl_signal_event_hook = rl_handle_signals;
	if (err(sigemptyset(&mask) || sigaddset(&mask, SIGTERM)
		|| sigaddset(&mask, SIGQUIT), "signal mask error"))//these return -1
		return ;
	ft_memset(&hands, 0, sizeof(struct sigaction));
	hands = {.sa_mask = mask, .sa_handler = sighands};//, .sa_flags = SA_RESTART};//exclude restart flag
	err(sigaction(SIGINT, &hands, NULL), "SIGINT setup error");
	err(sigaction(SIGQUIT, &hands, NULL), "SIGQUIT setup error");
}

/*
	cmd node would be:
prefix: enum: is && or || involved
cmd: the cmd name, actually I should call execute() regardless
io[2]: two fds, debating to not store pipe relationships in node. also dont init pipes on false branch
*/

int	good_syntax(t_cmd **cmd, char *input, int *last, t_env *env)//how about we dont fork
{
	if (!input || !input[0])
		return (0);//no op, dun change exit
	if (syntax_check(cmd, env, src))//this is not a child
	{
		*last = 1;
		return (0);
	}
	return (1);
}

int	buh_bye(int last, t_env *env)
{
	t_shnode *curr;

	curr = env->export;
	while (curr)
	{
		free(curr->str);
		curr = curr->next;
	}
	curr = env->env;
	while (curr)
	{
		free(curr->str);
		curr = curr->next;
	}
	free(env->export);
	ft_putstr("exit\n");
	rl_clear_history();
	return (last);
}

int	main(int c, char **v, char **e)
{
	int		last;
	char	*input;
	t_env	env;//stacc
	t_cmd	*cmd;//linked list

	//check_subshell(c, v, e);//keywords out of scope
	signal_init();//
	last = 0;
	cmd = NULL;
	env_init(&env, e);
	while (1)
	{
		errno = 0;
		input = readline();
		if (!input)
			return (buh_bye(last, &env));//say 'exit'//clear history func
		if (input[0])
			add_history(input);
		//LOCK SYNTAX CHECK BEHIND A FORK OMG then exit 1/cmd exit
		good_syntax(&cmd, input, &last, &env);//tokenise and not run if extra operators
		//"bash: fork: Resource temporarily unavailable"//DO NOT EXIT ON ERR, YOU ARE THE SHELL
		clean_cmd(&cmd);
	}
}
