#include "h_minishell.h"

//redo env malloc semantics
t_cmd	*cmd_node(void)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (ret)
	{
		ret->next = NULL;
		ret->str = NULL;
		ret->type = '\0';
	}
	else
		err(-1, "cmd node malloc");
	return (ret);
}

int	iscond(int c)
{
	return (c == '|' || c == '&' || c == '>' || c == '<');
}

int	iscontent(int c)
{
	return (!iscond(c) && !ft_isquote(c) && !ft_isspace(c) && c != 0);
}


//plez put sig check in while loop



int	super_check(char x, char y)
{
	int	a;
	int	b;
	int	c;
	int	d;

	a = (x == '|' || x == '&');
	b = (y == '|' || y == '&');
	c = (x == '>' || x == '<');
	d = (y == '>' || y == '<');
	return ((a && b) || (c && d));
}

int	syntax_err(char *str)
{
	ft_putstr_fd("minishell", 2);
	if (!str)
		str = "NULL";
	ft_putstr_fd("unexpected token near \"", 2);
	ft_putstr_fd(str, 2);
	write(2, "\n", 1);
	return (1);
}

//thank fuck heredoc takes a name too
//
int	actually_check(t_cmd **cmd, t_env *env)
{
	int		name;
	int		redir;
	char	c;
	char	last;
	t_cmd	*iter;

	name = 0;
	redir = 0;
	iter = *cmd;
	last = '\0';
	while (iter)
	{
		c = iter->type;
		if (c && !iscond(c) && (last == '<' || last == '>'))
			redir = 0;
		else if (c && !iscond(c))
			name = 1;
		else if (c == '>' || c == '<')
			redir = 1;
		else if (((c == '|' || c == '&') && (!name-- || redir))
			|| super_check(c, last))
			return (syntax_err(iter->str));//fail value...?//err log here
		last = c;//eh
	}
	return (!iter);
}

void	node_append(t_cmd **dst, t_cmd *ret)
{
	t_cmd	*iter;

	iter = *dst;
	while (iter && iter->next)
		iter = iter->next;
	if (!iter)
		*dst = ret;
	else
		iter->next = ret;
}

int	node_init(t_cmd **dst, char *src, int *cry)
{
	int		i;
	char	c;
	t_cmd	*ret;

	i = 0;
	c = src[0];
	while (!muh_number && ((iscond(c) && src[i] == c && i < 2)			//operator
		|| ((!iscond(c) && !ft_isquote(c)) && iscontent(src[i]))		//operand
			|| (isquote(c) && src[i] && src[i] != c)))					//quote, also operand
		i ++;
	ret = cmd_node();
	if (ret)
	{
		dst->str = ft_substr(src, 0, i);
		dst->type = c;//this field is a char now
	}
	if (!ret || !ret->str)
		*cry = (err(-(ret && !ret->str), "cmd node str malloc") || 1);
	node_append(dst, ret);
	return (i);
}

//do not expand env at this stage, treat as name nodes
//do assert closed quotes before expanding env
//oml do not code other redirections. not worth.
int	syntax_check(t_cmd **cmd, t_env *env, char *input)
{
	int	i;
	int	cry;

	i = 0;
	cry = 0;
	if (unclosed_check(input))
		return (prompt_err("unclosed quotes", 1));//returns n wit hout looking at it
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i ++;
		if (!input[i])
			break ;
		i += node_init(cmd, &input[i], &cry);
		if (cry)
			return (1);
	}
	return (actually_check(cmd, env));
}
