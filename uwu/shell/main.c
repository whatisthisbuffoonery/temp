#include "h_minishell.h"

int	signal_init(void)
{
	sigset_t			mask;
	struct sigaction	hands;

	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	rl_signal_event_hook = rl_handle_signals;
	ft_memset(&hands, 0, sizeof(struct sigaction));
	if (sigemptyset(&mask) || sigaddset(&mask, SIGTERM)
		|| sigaddset(&mask, SIGQUIT))
		return (-1);
	hands = {.sa_mask = mask, .sa_handler = sighands};//, .sa_flags = SA_RESTART};//exclude restart flag
	return (sigaction(SIGINT, &hands, NULL)
		+ sigaction(SIGQUIT, &hands, NULL));
}

/*
	cmd node would be:
prefix: enum: is && or || involved
cmd: the cmd name, actually I should call execute() regardless
io[2]: two fds, debating to not store pipe relationships in node. also dont init pipes on false branch
*/

int	syntax(t_cmd **cmd, char *input, int *last)
{
	pid_t	ret;
	int		n;

	if (input && input[0])
		ret = fork();
	else
		return (0);//no op, dun change exit
	if (!ret)
		good_syntax(cmd, src);//this is a child
	child_wait(ret);
	*last = check_exit(n);
	return (WIFEXITED(n) && !WEXITSTATUS(n));
}

int	main(int c, char **v, char **e)
{
	int		last;
	char	*input;
	t_cmd	*cmd;//linked list

	//check_subshell(c, v, e);//keywords out of scope
	if (signal_init())
		return (-err(-1, "some string"));//err
	last = 0;
	cmd = NULL;
	while (1)
	{
		input = readline();
		if (!input)
			return (buh_bye(last));//say 'exit'//clear history func
		if (input[0])
			add_history(input);
		//LOCK SYNTAX CHECK BEHIND A FORK OMG then exit 1/cmd exit
		if (syntax(&cmd, input, &last));//tokenise and not run if extra operators
		//"bash: fork: Resource temporarily unavailable"//DO NOT EXIT ON ERR, YOU ARE THE SHELL
		clean_cmd(&cmd);
//		if (errno)
//			return (1);//debatable exit code, wait, exit().
	}
}
