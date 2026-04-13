#include "h_minishell.h"

int	iscond(int c)
{
	return (c && (c == '|' || c == '&' || c == '>' || c == '<'));
}

int	iscontent(int c)
{
	return (!iscond(c) && !ft_isquote(c) && !ft_isspace(c));
}


//put sig check at the start of each major step, putting it in while loops will be a bit cluttered



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
	return ((a && b) || (c && d) || (c && a));
}

int	syntax_err(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	if (!str)
		str = "NULL";
	ft_putstr_fd("unexpected token near \"", 2);
	ft_putstr_fd(str, 2);
	write(2, "\"\n", 2);
	return (1);
}

//heredoc takes a name too
//expand envs and merge connected name nodes, inherit type field of first node
int	actually_check(t_cmd **cmd, t_env *env)
{
	int		name;
	int		redir;
	char	c;
	char	last_space;//repurposed
	t_cmd	*iter;

	name = 0;
	redir = 0;
	iter = *cmd;
	last_space = 1;
	while (iter)
	{
		c = iter->type;
		name += (!name && !redir && last_space && !iscond(c));
		redir -= (redir && !iscond(c));
		redir += (!redir && (c == '>' || c == '<'));
		if (((c == '|' || c == '&' || !iter->next) && (!name-- || redir))
			|| super_check(c, iter->next->type) || /*!ft_strcmp(iter->str, "&")*/)//single & not required
			return (syntax_err(iter->str));
		last_space = iter->end_space;
		iter = iter->next;
	}
	return (0);
}

/*syntax checker section------------------------------------------------------------*/

t_cmd	*cmd_node(char *src, int i, char c, int *cry)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (!ret)
	{
		err(-1, "cmd node malloc");
		return (NULL);
	}
	ret->str = ft_substr(src, (ft_isquote(c) != 0), i);
	ret->next = NULL;
	ret->env = NULL;
	ret->type = '\0';
	if (!ret->str)
		*cry = (err(-1, "cmd node str malloc"));
	ret->type = c;
	if (ret->str && !ft_strcmp(ret->str, "&"))//single & not required
		ret->type = '@';
	ret->end_space = ft_isspace(src[i + (src[i] && ft_isquote(c))]);//bool
	return (ret);
}

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

//this splits words, quotes, and operators &, |, >, <

//splitting words from quotes is done for simplicity,
//but should be recombined if they were not separated by whitespace

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

/*cmd node utilities-------------------------------------------*/

//str sitting on '$'
int	shnode_strlen(t_shnode *env)
{
	if (env && env->str)
		return (ft_strlen(env->str));
	return (0);
}

t_shnode	*find_env(char *str, t_shnode *list, int n)
{
	while (list && (list->name[n] || ft_strncmp(str, list->name, n)))
		list = list->next;
	return (list);
}

t_shnode	*expansion_dup(t_shnode *src)
{
	t_shnode	*ret;

	ret = malloc(sizeof(t_shnode));
	if (!ret)
	{
		err(-1, "expansion malloc");
		return (NULL);
	}
	ret->name = src->name;
	ret->str = src->str;
	ret->next = NULL;
	return (ret);
}

/*shnode utilities------------------------------------------------------------*/

int add_expansion(t_cmd *dst, t_shnode *env, int *index)
{
	t_shnode	*ret;
	char		*str;
	int			i;

	i = 1;
	str = &dst->str[*index + 1];//dollar offset
	while (iscontent(str[i]))
		i ++;
	*index += i + 1;//use env name len plus dollar
	if (find_env(str, dst->env, i))
		return (0);
	env = find_env(str, env, i);
	ret = expansion_dup(env);//mallocs a node, does not malloc the strings so dont free those
	if (!ret)
		return (1);
	shnode_append(&dst->env, ret);
	return (0);
}

void	copy_wrapper(char *src, char *dst, int *i, int *len)
{
	if (dst)
		dst[*len] = src[*i];
	*i += 1;
	*len += 1;
}

void	concat_wrapper(t_cmd *dst, char *ret, int *i, int *len)
{
	t_shnode	*iter;
	char		*str;
	int			k;

	k = 0;
	iter = dst->env;
	str = &dst->str[*i + 1];
	while (iscontent(str[*i + k]))
		k ++;
	while (iter && ft_strncmp(str, iter->name, k))
		iter = iter->next;
	if (ret && iter)
		len += ft_strlcat(ret, iter->str, -1);
	else if (iter)
		len += ft_strlen(iter->str);
	*i += k + 1;
}

int	use_expansion(t_cmd *dst, char *ret)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (ret)
		ret[0] = '\0';
	while (dst->str[i])
	{
		if (dst->str[i] == '$' && iscontent(dst->str[i + 1]))
			concat_wrapper(dst, ret, &i, &len);//either strlen or strlcat
		else if (dst->str[i]
			&& (dst->str[i] != '$' || !iscontent(dst->str[i + 1])))
			copy_wrapper(dst->str, ret, &i, &len);//copy one char//yes we copy dollar sign if env name is invalid
	}
	if (!ret
		&& (!err(-!malloc_cond((void **) &ret, len), "expansion result malloc")))
		return (use_expansion(dst, ret));
	else if (!ret)
		return (1);
	free(dst->str);
	dst->str = ret;
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
				&& add_expansion(iter, env, &i))
				return (1);
			i += (iter->str[i] && iter->str[i] != '$');
		}
		iter = iter->next;
	}
	*iter = *cmd;
	while (iter)//move this over to command forking side, expand envs before each command, not before *all* commands
	{
		if (iter->type != '\'' && iter->env && use_expansion(iter, NULL))
			return (1);
		iter = iter->next;
	}
	return (0);
}

/*env expansion section-------------------------------------------------------------------------*/

void	join_names_cont(t_cmd *head, int i, char *ret)
{
	int		k;

	k = 0;
	free(head->str);
	head->str = ret;
	while (k++ < i)//exclude head node iteration now
		cmd_node_del(&head, head->next);//this will be used in main as well
}

//i == 1 means join two nodes together, i == 2 means three nodes, etc
int	join_name_nodes(t_cmd *head, int i)
{
	t_cmd	*iter;
	int		len;
	int		k;
	char	*ret;

	iter = head;
	len = 0;
	k = 0;
	while (k++ <= i)
	{
		len += ft_strlen(iter->str);
		iter = iter->next;
	}
	ret = ft_calloc(len + 1, sizeof(char));//strlcat needs at least the first char to be null
	if (!ret)
		return (err(-1, "join str malloc"));
	iter = head;
	k = 0;
	while (k++ <= i)
	{
		ft_strlcat(ret, iter->str, -1);//this puts its own null terminator
		iter = iter->next;
	}
	join_names_cont(head, i, ret);
	return (0);
}

int	rejoin_str(t_cmd **cmd)
{
	int		i;
	t_cmd	*iter;
	t_cmd	*head;

	iter = *cmd;
	head = *cmd;
	i = 0;
	while (iter)
	{
		if (!iter->end_space && iter->next && !iscontent(iter->next->type))
			i ++;
		else if (i && join_name_nodes(head, i, &iter))//just modify next ptr and free the rest
			return (1);
		else
		{
			iter = head;
			head = head->next;
			i = 0;
		}
		iter = iter->next;
	}
	return (0);
}

/*this section accounts for [a"b"] being split up into [a], [b]----------------------------------------*/

//do assert closed quotes before expanding env
//oml do not code other redirections. not worth.
//cleanup funcs are left for later
//todo: reject glob patterns for redirections, but that should be done while evaluating each command at runtime
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
		|| (!expand_str(cmd, env->env)
				/*&& rejoin_str(cmd)*/ //due to moving env expansion over, this is moving over too.
					&& actually_check(cmd, env)));//0 on success
}
