#include "h_minishell.h"
typedef struct s_node
{
	t_node_kind		kind;
	char			**argv; // N_CMD  – argv array (NULL-terminated) 
	int				argc;
	char			*redir_op;		// N_REDIR – attached to the cmd or group it belongs to 
	char			*redir_target;
	struct s_node	*redir_next;	// linked list of redirects on one cmd 
	struct s_node	*left;			// N_PIPE / N_AND / N_OR / N_GROUP 
	struct s_node	*right;			// unused for N_GROUP 
}					t_node;

//add a word_next field to t_cmd
typedef struct s_node
{
	t_node_kind		kind;
	t_cmd			*argv; // N_CMD  – argv array (NULL-terminated) //cmd name is first item
	int				argc; //figure out later
	t_cmd			*redir_op;		// mutually exclusive with argv
	t_cmd			*redir_target;	//this too
	struct s_node	*redir_next;	// linked list of redirects on one cmd // again DO NOT FILL THE OTHER TWO FIELDS DIRECTLY
	struct s_node	*left;			// N_PIPE / N_AND / N_OR / N_GROUP //
	struct s_node	*right;			// unused for N_GROUP 
}					t_node;

int	ismeta(char c)
{
	return (isbracket((*tok)->type) || iscond((*tok)->type));
}

int	ast_iscond(t_cmd *tok)
{
	return (!ft_strcmp(tok->str, "||") || !ft_strcmp(tok->str, "&&"));
}

int	isarg(char c)
{
	return (!isbracket(c) && !iscond(c) && !isredir(c));
}

t_node_kind	find_kind_op(t_cmd *tok)
{
	if (!ft_strcmp(tok->str, "&&"))
		return (N_AND);
	else if (!ft_strcmp(tok->str, "||"))
		return (N_OR);
	return (N_ILLEGAL);
}//really isnt necessary but eh

t_node	*node_new(t_node_kind kind, int *complain)
{
	t_node	*ret;

	ret = NULL;
	if (kind != N_ILLEGAL)
		ret = ft_calloc(sizeof(t_node), 1);
	if (!ret)
	{
		*complain = 1;
		if (kind != N_ILLEGAL)
			ft_err(-1, "ast node malloc");
		return (NULL);
	}
	ret->kind = kind;
	return (ret);
}

void	cmd_pop(t_cmd **tok)
{
	t_cmd	*head;

	if (!*tok)
		return ;
	head = (*tok)->next;
	cmd_delone(*tok);
	*tok = head;
}

t_node	*parse_one_redir(t_cmd **tok, int *stop)
{
	t_node	*r;

	r = node_new(N_REDIR, stop);
	if (!r)
		return (NULL);
	r->redir_op = subcmd(tok, single);//increment
	if (!*tok || !isarg((*tok)->type))
	{
		ft_putstr_fd("syntax error: redirect followed by ", 2);
		if (!*tok)
			ft_putstr_fd("EOF", 2);
		else
			ft_putstr_fd((*tok)->str, 2);
		ft_putstr_fd("\n", 2);
		*stop = 1;
	}
	else
		r->redir_target = subcmd(tok, single);//still counting on word_next
	return (r);
}

//check redir_next usage
t_node	*parse_redir_group(t_cmd **tok, int *stop)
{
	t_node	*head;
	t_node	*tail;//eh
	t_node	*r;

	head = NULL;
	tail = NULL;
	while (*tok && !*stop && isredir((*tok)->type))
	{
		r = parse_one_redir(tok, stop);
		if (!head)
			head = r;
		if (tail)
			tail->redir_next = r;
		tail = r;
	}
	return (head);
}

void	node_append(t_node **dst, t_node *src)
{
	t_node	*iter;

	iter = *dst;
	while (iter && iter->next)
		iter = iter->next;
	if (!iter)
		*dst = src;
	else
		iter->next = src;
}

//cmd word idea: start is head, word_next = subcmd(&head->next, isjoined)
t_node	*parse_simple(t_cmd **tok, int *stop)
{
	t_node	*new_cmd;

	if (!*tok || !(*tok)->type || ismeta((*tok)->type))//accept redir
	{
		ft_putstr_fd("expected command, got ", 2);
		if (!*tok)
			ft_putstr_fd("EOF", 2);
		else
			ft_putstr_fd((*tok)->str, 2);
		ft_putstr_fd("\n", 2);
		*stop = 1;
		return (NULL);
	}
	new_cmd = node_new(N_CMD, stop);//does not increment
	if (!new_cmd)
		return (NULL);
	while (*tok && !*stop && (*tok)->type && !ismeta((*tok)->type))
	{
		if (isredir((*tok)->type))
			node_append(&new_cmd->redir_next, parse_one_redir(tok, stop));//make a func
		else
			cmd_node_append(&new_cmd->argv, subcmd(tok, single));//increment
	}
	return (cmd);
}

//veto open bracket check
t_node	*parse_group(t_cmd **tok, int *stop)
{
	t_node	*new_group;

	cmd_pop(tok);
	new_group = node_new(N_GROUP, stop);
	if (!new_group)
		return (NULL);
	new_group->left = parse_list(tok, stop);
	if (*stop)
		return (new_group);
	if (!*tok || (*tok)->type != ')')
	{
		ft_putstr_fd("syntax error: unclosed brackets\n", 2);
		*stop = 1;
		return (new_group);
	}
	cmd_pop(tok);
	new_group->redir_next = parse_redir_group(tok, stop);
	return (new_group);
}

t_node	*parse_command(t_cmd **tok, int *stop)
{
	if (!*tok)
	{
		ft_putstr_fd("syntax error: unexpected end of input\n", 2);
		*stop = 1;
		return (NULL);
	}
	if ((*tok)->type == '(')
		return (parse_group(tok, stop));
	return (parse_simple(tok, stop));
}

//left = pipe symbol, right = command
//execution idea: recursive pipe manager increments count
t_node	*parse_pipeline(t_cmd **tok, int *stop)
{
	t_node	*L;
	t_node	*R;
	t_node	*new_pipe;

	L = parse_command(tok, stop);
	if (!L || *stop)
		return (L);
	while (*tok && !*stop && !ft_strcmp((*tok)->str, "|"))
	{
		new_pipe = node_new(N_PIPE, stop);
		if (!new_pipe)
			return (L);
		cmd_pop(tok);
		R = parse_command(tok, stop);//veto failure catch
		new_pipe->left = L;
		new_pipe->right = R;
		L = new_pipe;
	}
	return (L);
}

t_node	*parse_list(t_cmd **tok, int *stop)
{
	t_node	*L;
	t_node	*R;
	t_node	*new_op;

	L = parse_pipeline(tok, stop);
	if (!L || *stop)
		return (L);
	while (*tok && !*stop && ast_iscond(*tok))
	{
		new_op = node_new(find_kind_op(*tok), stop);
		if (!new_op)
			return (L);
		cmd_pop(tok);
		R = parse_pipeline(tok, stop);//veto failure catch
		new_op->left = L;
		new_op->right = R;
		L = new_op;
	}
	return (L);
}

t_node	*parse(t_cmd *tok)
{
	int		stop;
	t_node	*nodes;

	stop = 0;
	nodes = parse_list(&tok, &stop);
	if (tok && !stop)
	{
		ft_putstr_fd("syntax error: unexpected token '", 2);
		ft_putstr(tok->str, 2);
		ft_putstr_fd("'\n", 2);
		stop = 1;
	}
	if (stop)
	{
		ast_free(nodes);
		nodes = NULL;
	}
	return (nodes);
}
