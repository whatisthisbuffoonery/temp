#include "h_minishell.h"

//redo env malloc semantics

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
t_cmd	*cmd_node(char *src, int i, char c, int *cry)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (!ret)
	{
		err(-1, "cmd node malloc");
		return (NULL);
	}
	ret->next = NULL;
	ret->str = NULL;
	ret->env = NULL;
	ret->type = '\0';
	ret->str = ft_substr(src, (ft_isquote(c) != 0), i);
	ret->type = c;//this field is a char now
	if (!ret->str)
		*cry = (err(-1, "cmd node str malloc"));
	else
		ret->end_space = ft_isspace(src[i + (src[i] && ft_isquote(c))]);//bool
	return (ret);
}
//heredoc takes a name too
//end space uhhhhhhhhhh
//expand envs and merge connected name nodes, inherit type field of first node

void	cmd_node_append(t_cmd **dst, t_cmd *ret)
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
	ret = cmd_node(src, i, c, cry);
	cmd_node_append(dst, ret);
	return (i + (ft_isquote(c) != 0));
}
/*
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

//gave up here
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
*/

//str sitting on '$'

int	shnode_strlen(t_shnode *env)
{
	if (env && env->str)
		return (ft_strlen(env->str));
	return (0);
}

int add_expansion(t_cmd *dst, t_shnode *env, int *index)
{
	t_shnode	*ret;
	char		*str;
	int			i;

	i = 1;
	str = &dst->str[*index];
	while (iscontent(str[i]))
		i ++;
	while (env && ft_strncmp(&str[1], env->name, i - 1))
		env = env->next;
	if (!malloc_cond((void **) &ret, (sizeof(t_shnode)))
		|| !malloc_cond((void **) &ret->str, (shnode_strlen(env)) + 1))
		return (err(-1, "expansion malloc"));
	*index += i + 1;//use env name len
	i = -1;
	while (env && env->str[++i])
		ret->str[i] = env->str[i];
	ret->str[i + !env] = '\0';
	ret->next = NULL;
	shnode_append(&dst->env, ret);
	return (0);
}

//stopped here ish
int	use_expansion(t_cmd *dst, char *ret)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (dst->str[i])
	{
		if (dst->str[i] == '$' && iscontent(dst->str[i + 1]))
			concat_wrapper(dst, ret, &i, &len);//either strlen or strlcat
		else if (dst->str[i]
			&& (dst->str[i] != '$' || !iscontent(dst->str[i + 1])))
		{
			len ++;
			copy_wrapper(dst->str[i], ret);//copy one char
	}
	if (!ret
		&& (!err(-!malloc_cond((void **) &ret, len), "expansion result malloc")))
		return (use_expansion(dst, ret));
	else if (!ret)
		return (1);
	return (0);
}

int	expand_str(t_cmd **cmd, t_shnode *env)
{
	t_cmd	*iter;
	int		i;

	while(iter)
	{
		i = 0;
		while (iter->str[i] && iter->type != '\'')
		{
			if (iter->str[i] == '$' && iscontent(iter->str[i + 1])
				&& add_expansion(iter, env, &i))//memcpy//env names dont have $ in them
				return (1);
			i += (iter->str[i] && iter->str[i] != '$');
		}
		iter = iter->next;
	}
	*iter = *cmd;
	while (iter)
	{
		if (iter->type != '\'' && iter->env && use_expansion(iter))
			return (1);
		iter = iter->next;
	}
	return (0);
}

//do assert closed quotes before expanding env
//oml do not code other redirections. not worth.
int	syntax_check(t_cmd **cmd, t_env *env, char *input)
{
	int	i;
	int	cry;

	i = 0;
	cry = 0;
	if (unclosed_check(input))
		return (prompt_err("unclosed quotes"));
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
