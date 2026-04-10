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
		ret->env = NULL;
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
//end space uhhhhhhhhhh
//expand envs and merge connected name nodes, inherit type field of first node
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

//check for ending whitespace, ls'>'wa should stay as one element
int	node_init(t_cmd **dst, char *src, int *cry)
{
	int		i;
	char	c;
	t_cmd	*ret;

	i = 1;//oh mah gah
	c = src[0];
	while (!muh_number && ((iscond(c) && src[i] == c && i < 2)			//operator
		|| (iscontent(c) && iscontent(src[i]))							//operand
			|| (ft_isquote(c) && src[i] && src[i] != c)))				//quote, also operand
		i ++;
	ret = cmd_node();
	if (ret)//shove this out tbh
	{
		ret->str = ft_substr(src, (ft_isquote(c) != 0), i);
		ret->type = c;//this field is a char now
	}
	if (!ret || !ret->str)
		*cry = (err(-(ret && !ret->str), "cmd node str malloc") || 1);
	ret->end_space = ft_isspace(src[i + (src[i] && ft_isquote(c))]);//bool
	node_append(dst, ret);
	return (i + (ft_isquote(c) != 0));
}

//BLYAT I have to enforce good env var names
//assume good names from bash //env contents can be anything
//IF empty env name (i.e. "$" or "$<" using dquotes) 
int	match_env(char *input, char *dst, t_shnode *env, int *len)
{
	int			k;
	int			i;
//	t_shnode	*iter;

	i = 0;
	k = 0;
//	iter = env;
	while (ft_strchr(input, '$'))
	{
		while (input[i] != '$')
			i ++;
		input = &input[i + 1];
		k += i;
		i = 0;
		while (input[i] && !iscontent(input[i]))
			i ++;
//		while (iter && ft_strncmp(env->str, input, i))
//			iter = iter->next;
		k += match_the_string(input, dst, env, &i);
	}
	return ();
}
//nah nah nah this sucks go make another list for expandable items

int	expand_the_str(t_cmd *iter, t_shnode *env, char *ret)
{
	int		i;
	int		len;
	char	*prefix;

	i = 0;
	len = 0;
	while (iter->str[i])
	{
		if (iter->str[i] != '$')
		{
			i ++;
			len ++;
			continue ;
		}
		i += match_env(&iter->str[i], ret, env, &len);
	}
	if (!ret)
		return (-!malloc_cond((void **) &ret, len + 1)
			|| expand_the_str(iter, env, ret));
	free(iter->str);
	iter->str = ret;
	return (0);
}


//verify env is the one without empty items
//if (char after '$' iscontent)
//try the python size thing for all structs?
int	expand_init(t_cmd **cmd, t_shnode *env)
{
	t_cmd	*iter;
	int		i;
	int		k;

int	expand_str(t_cmd **cmd, t_shnode *env)
{
	t_cmd	*iter;
	char	*tmp;
	int		len;

	if (expand_init(cmd, env))//my cmd node now contains a different linked list of env vars. i hate myself
		return (1);
	iter = *cmd;
	while (iter)
	{
		if (iter->type != '\'' && ft_strchr(iter->str, '$')
			&& err(expand_the_str(iter, env, NULL), "str expansion malloc"))
			return (1);
		iter = iter->next;
	}
	iter = *cmd;
	while (iter && iter->next)
	{
		if (!iscond(iter->type) && !iscond(iter->next->type)
			&& !iter->end_space
				&& err(join_the_str(&iter, env), "cmd str malloc"))
			return (1);
		iter = iter->next;
	}
	return (0);
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
		return (prompt_err("unclosed quotes"));//will I make a general manager for all the different formats?
	while (input[i] && !muh_number)
	{
		while (ft_isspace(input[i]))
			i ++;
		if (!input[i])
			break ;
		i += node_init(cmd, &input[i], &cry);
		if (cry)
			return (1);
	}
	return (muh_number
		|| (!expand_str(cmd, env->env) && actually_check(cmd, env)));
}
