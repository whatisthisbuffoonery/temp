#include "h_minishell"

int	node_init(t_list **cmd, t_list *env, char *input, int *cry)//cmd has a t_list field
{
	int		i;
	char	*ret;

	s

int	syntax_check(t_list **cmd, t_list *env, char *input)//change cmd to t list
{
	int	i;
	int	cry;

	while (input[i])
	{
		while (ft_isspace(input[i]))
			i ++;
		if (!input[i])
			break;
		i += node_init(cmd, env, &input[i], &cry);
		if (muh_number || cry)
			return (1);
	}
	return ();
}
