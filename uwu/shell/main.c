#include "h_minishell.h"

int	signal_init(void)
{
	sigset_t			mask;
	struct sigaction	hands;

	if (sigemptyset(&mask) || sigaddset(&mask, SIGTERM)
		|| sigaddset(&mask, SIGQUIT))
		return (-1);
	hands = {.sa_mask = mask, .sa_handler = sighands, .sa_flags = SA_RESTART};
	return (sigaction(SIGINT, &hands, NULL)
		+ sigaction(SIGQUIT, &hands, NULL));
}

/*
	cmd node would be:
prefix: enum: is && or || involved
cmd: the cmd name, actually I should call execute() regardless
io[2]: two fds, debating to not store pipe relationships in node. also dont init pipes on false branch
*/

int	main(int c, char **v, char **e)
{
	int		last;
	char	*input;
//	t_cmd	*cmd;//linked list

	check_subshell(c, v, e);
	last = 0;
	if (signal_init())
		return (-err(-1, "some string"));//err
	while (1)
	{
		input = readline();
		if (!input)
			return (buh_bye(last));//say 'exit'
		if (input[0])
			add_history(input);
		if (good_syntax
		chew_list(input);
	}
}
