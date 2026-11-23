#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

typedef struct node {
    enum {
        ADD,
        MULTI,
        VAL
    }   type;
    int val;
    struct node *l;
    struct node *r;
}   node;

node    *new_node(node n)
{
    node *ret = calloc(1, sizeof(node));
    if (!ret)
        return (NULL);
    *ret = n;
    return (ret);
}

void    destroy_tree(node *n)
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

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of input\n");
}

int accept(char **s, char c)
{
    if (**s == c)
    {
        (*s)++;
        return (1);
    }
    return (0);
}

//this function sucks
int expect(char **s, char c)
{
    if (accept(s, c))
        return (1);
    unexpected(**s);
    return (0);
}

node	*append_node(char **s)
{
	node	tmp;

	tmp.l = NULL;
	tmp.r = NULL;
	tmp.val = 0;
	if (isdigit(**s))
	{
		tmp.type = VAL;
		tmp.val = **s - '0';
	}
	else if (**s == '+')
		tmp.val = ADD;
	else if (**s == '*')
		tmp.val = MULTI;
	else
	{
		unexpected(**s);
		return (NULL);
	}
	(*s)++;
	return (new_node(tmp));
}

node    *parse_expr(char **s, int bracket)
{
	node	*l = NULL;
	node	*curr = NULL;

    while (1)
	{
		if (accept(s, '('))
			curr = parse_expr(s, bracket + 1);
		else if (accept(s, ')'))
			bracket --;
		else
			curr = append_node(s);
		if (!curr || bracket < 0)
			break ;
		increment(&l, curr);
	}
	if (!curr || bracket
    return (l);
}

int eval_tree(node *tree)
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

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
	char	*tmp = argv[1];
    node *tree = parse_expr(&tmp, 0);
    if (!tree)
        return (1);
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
}
