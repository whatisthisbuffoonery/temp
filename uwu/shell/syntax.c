#include "h_minishell.h"

char	**parse_string(char *src, int *i)
{
	int		end;
	char	**ret;

	end = *i;
	while (src[end])
	{
		while (src[end] && (ft_isalpha(src[end]) || ft_isspace(src[end])))
			end ++;
		if (src[end] == '$' && src[end + 1] == '?')//aggresive matching
			//fuk
	if (src[end])
		ret = use_moar_malloc(src, i, end);
	else
		ret = ft_split(&src[*i], ' ');
	*i = end;
	return (ret);//might be null
}

//tf does a guy do to divide between tokenisation

int	add_token(t_cmd **cmd, char *src, int *i)
{
	t_cmd	*ret;
	t_cmd	*last;

	last = *cmd;
	while (last && last->next)
		last = last->next;
	ret = malloc(sizeof(t_cmd));
	if (ret)
		ret->arr = parse_string(src, i);//i now need a split that knows where to stop, fu-
	if (!ret || !ret->arr)
	{
		free(ret)
		return (err(-1, "malloc"));
	}
	if (last)
		last->next = ret;
	else
		*cmd = ret;
	return (0);
}

int	good_syntax(t_cmd **cmd, char *src)
{
	int	i;

	i = 0;
	while (src[i])//no. ft split the whole thing.
	{
		while (isspace(i))
			i ++;
		if (add_token(cmd, src, &i))//malloc//stop on next item
			return (1);
	}
	return (0);
}
