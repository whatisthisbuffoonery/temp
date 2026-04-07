#include "h_minishell.h"

static void	window_shopping(t_shnode *curr, t_shnode *a, t_shnode *b)
{
	t_shnode	*iter;

	while (a && b)
	{
		if (ft_strcmp(a, b) < 0)
		{
			curr->next = a;
			a = a->next;
		}
		else
		{
			curr->next = b;
			b = b->next;
		}
		curr = curr->next;
	}
	iter = b;
	if (!b)
		iter = a;
	while (iter)
	{
		curr->next = iter;
		curr = curr->next;
		iter = iter->next;
	}
}

static void	merge_split(t_shnode **head, t_shnode **a, t_shnode **b)
{
	t_shnode	*i;
	t_shnode	*k;

	i = *head;
	k = NULL;
	*a = i;
	if (i)
		k = i->next;
	while (k && k->next)
	{
		i = i->next;
		k = k->next->next;
	}
	if (i)
		*b = i->next;
	if (*b)
		i->next = NULL;
}

static void	merge_sort(t_shnode **head)
{
	t_shnode	*a;
	t_shnode	*b;

	a = NULL;
	b = NULL;
	merge_split(head, &a, &b);
	if (a && a->next)
		merge_sort(&a);
	if (b && b->next)
		merge_sort(&b);
	if (b && ft_strcmp(a, b) > 0)
	{
		*head = b;
		b = b->next;
	}
	else
	{
		*head = a;
		a = a->next;
	}
	window_shopping(*head, a, b);
}

void	env_init_cont(t_env *dst, int count)
{
	t_shnode	*iter;

	iter = dst->export;
	while (iter && 

//init shell level, leave cd dash alone
//mild proposal to standardise cmd nodes in order to consider per malloc init here
void	env_init(t_env *dst, char **e)
{
	int			i;
	int			k;
	t_shnode	*ret;

	i = ft_ptrlen(e);
	ft_memset(dst, 0, sizeof(t_env));
	if (!malloc_cond((void **) &ret, (2 * i) * sizeof(t_shnode)))
		return ;
	k = -1;
	while (++k + 1 < 2 * i)
		ret[k].next = ret[k + 1];
	ret[k].next = NULL;
	ret[i - 1].next = NULL;
	k = -1;
	dst->export = ret;//either change this to malloc per node, or put another field to track where this arr ends
	dst->env = &ret[i];
	while (e[++k])
	{
		ret[k].str = ft_strdup(e[i]);
		ret[i + k].str = ft_strdup(e[i]);
		if (!ret[k].str || !ret[i + k].str)
			break ;//yeah no, do per malloc
	}
	merge_sort(&dst->env);
	env_init_cont(dst, i);
}
