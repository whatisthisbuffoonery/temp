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

t_node	*parse_one_redir(t_cmd **tok, int *stop)
{
	t_node	*r;

	r = node_new();
	if (!r)
		return (NULL);
	r->redir_op = subcmd(tok, single);//increment
	if ("null or not word")
		//complain, return r damn you
	r->redir_target = subcmd(tok, single);
	return (r);
}

//check redir_next usage
t_node	*parse_redirs(t_cmd **tok, int *stop)
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

//cmd word idea: start is head, word_next = subcmd(&head->next, isjoined)
t_node	*parse_simple(t_cmd **tok, int *stop)
{
	t_node	*new_cmd;
	t_node	*r;

	if (ismeta((*tok)->type))//accept redir
		//parse_err "command", cmd str/EOF, stop = 1, return null
	new_cmd = node_new();//does not increment
	if (!new_cmd)
		return (NULL);
	while (*tok && !*stop && !ismeta((*tok)->type))
	{
		if (isredir((*tok)->type))
			redir_append(new_cmd, parse_one_redir(tok, stop));//make a func
		else
			argv_append(new_cmd, just_grab_one(tok));//increment
	}
	return (cmd);
}

t_node	*parse_group(t_cmd **tok, int *stop)
{
	t_node	*new_group;

	new_group = node_new();
	if (!new_group)
		return (NULL);
	new_group->left = parse_list(tok, stop);
	if (*tok && (*tok)->type != ')')//increment if is close bracket
		//tantrum
	new_group->redir_next = parse_redirs(tok, stop);
	return (new_group);
}
}

t_node	*parse_command(t_cmd **tok, int *stop)
{
	if (!*tok)
		//complain, return null
	if ((*tok)->type == '(')
		return (parse_group(tok, stop));
	return (parse_simple(tok, stop));
}

t_node	*parse_pipeline(t_cmd **tok, int *stop)
{
	t_node	*L;
	t_node	*R;
	t_node	*new_pipe;

	L = parse_command(tok, stop);
	if (!L || *stop)
		return (L);
	while (*tok && !ft_strcmp((*tok)->str, "|"))
	{
		new_pipe = node_new();//again undecided
		if (!new_pipe)
			return (L);
		////INCREMENT BEFORE CALLING
		R = parse_command(tok, stop);
		if (!R || *stop)
			return (L);
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
	while (*tok && iscond((*tok)->type))
	{
		new_op = node_new(thing, stop);//undecided between passing in the whole node or just type
							//pass stop as well
		if (!new_op)
			return (L);
		////INCREMENT BEFORE CALLING
		R = parse_pipeline(tok, stop);
		if (!R || *stop)
			return (L);
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

	complain = 0;
	nodes = parse_list(&tok, &stop);
	if (stop)
		//cleanup and null
	if (tok)
		//complain unexpected token
}
