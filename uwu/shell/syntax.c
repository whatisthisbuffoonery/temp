#include "h_minishell.h"

//err log: syntax error near unexpected token [fatal token]
//we have to take this out of libft to indicate quotes used
int	assign_types(t_cmd **cmd)
{
	t_cmd	*iter;
	t_type	last;
	int		flag;

	last = empty;
	iter = *cmd;
	while (iter)
	{
		if (iter->type != empty)
		{
			iter = iter->next;
			continue ;
		}
		if (iscarrot(iter->str[0]))
			redirect(iter, &flag);
		else if (iscond(iter->str[0]))// pipes and ampersands
			cond(iter, &flag);
		else
			name(iter, &flag);//checks between name and num
	}
	return (actually_check(cmd));
}

int	syntax_check(t_cmd **cmd, t_env *env, char *input)
{
	char	**arr;
	int		i;

	arr = parsed_argsplit(input);
	if (arr)
		*cmd = malloc(ft_ptrlen(arr) * sizeof(t_cmd));
	if (!arr || !*cmd)
		return (split_cleanup(arr) || err(-1, "malloc error"));
	i = 0;
	while (arr[i])
	{
		(*cmd)[i].str = env_check(arr[i], env->env);
		(*cmd)[i].next = &(*cmd)[i + 1];
		if (!(*cmd)[i].str)
			return (split_cleanup(arr) || err(-1, "malloc error"));
		i ++;
	}
	(*cmd)[i - 1].next = NULL;
	return (assign_types(cmd));
}
