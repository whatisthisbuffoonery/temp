#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

typedef struct node
{
	enum
	{
		ADD,
		MULTI,
		VAL
	}	type;
	int	val;
	struct node	*l;
	struct node	*r;
}	node;

node		*new_node(node n)
{
	node *ret = calloc(1, sizeof(node));
	if (!ret)
		return (NULL);
	*ret = n;
	return (ret);
}

void		destroy_tree(node *n)
{
	if (!n)
		return ;
	if (n->type != VAL)
	{
		destroy_tree(n->l);
		destroy_tree(n->r);
	}
	free(n);
}

void		unexpected(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input\n");
}

int	accept(char **s, char c)
{
	if (**s == c)
	{
		(*s)++;
		return (1);
	}
	return (0);
}

int	expect(char **s, char c)
{
	if (accept(s, c))
		return (1);
	unexpected(**s);
	return (0);
}

node		*parse_add(char **s, int bracket);

node	*parse_num(char **s)
{
	node	tmp;

	if (accept(s, '('))
		return (parse_add(s, 1));
	else if (!isdigit(**s))
		return ((unexpected(**s)), NULL);
	tmp.type = VAL;
	tmp.l = NULL;
	tmp.r = NULL;
	tmp.val = **s - '0';
	(*s) ++;
	return (new_node(tmp));
}

node	*parse_mult(char **s)
{
	node	*l = parse_num(s);
	node	*curr;
	node	tmp;

	tmp.type = MULTI;
	while (l && accept(s, '*'))
	{
		curr = parse_num(s);
		if (!curr)
			return ((destroy_tree(l)), NULL);
		tmp.l = l;
		tmp.r = curr;
		l = new_node(tmp);
	}
	return (l);
}

node		*parse_add(char **s, int bracket)
{
	node	*l = parse_mult(s);
	node	*curr;
	node	tmp;

	tmp.type = ADD;
	while (l && accept(s, '+'))
	{
		curr = parse_mult(s);
		if (!curr)
			return ((destroy_tree(l)), NULL);
		tmp.l = l;
		tmp.r = curr;
		l = new_node(tmp);
	}
	
//	if (l && bracket && !expect(s, ')'))
//	{
//		destroy_tree(l);
//		return (NULL);
//	}
	
	if (l && bracket && !expect(s, ')') && !**s)
		(*s)--;
	return (l);
}

node	*parse_expr(char *s)
{
	node	*tree = parse_add(&s, 0);

	if (*s)
	{
		destroy_tree(tree);
		return (NULL);
	}
	return (tree);
}

int	eval_tree(node *tree)
{
	switch (tree->type)
	{
		case ADD:
			return (eval_tree(tree->l) + eval_tree(tree->r));
		case MULTI:
			return (eval_tree(tree->l) * eval_tree(tree->r));
		case VAL:
			return (tree->val);
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	node *tree = parse_expr(argv[1]);
	if (!tree)
		return (1);
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
}
