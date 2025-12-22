#include "header_ps.h"

static void	window_shopping(t_list *curr, t_list *a, t_list *b, t_list *iter)
{
	while (a && b)
	{
		if (a->num < b->num)
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

static void	merge_split(t_list **head, t_list **a, t_list **b)
{
	t_list	*i;
	t_list	*k;

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

static void	merge_sort(t_list **head)
{
	t_list	*a;
	t_list	*b;

	a = NULL;
	b = NULL;
	merge_split(head, &a, &b);
	if (a && a->next)
		merge_sort(&a);
	if (b && b->next)
		merge_sort(&b);
	if (b && a->num > b->num)
	{
		*head = b;
		b = b->next;
	}
	else
	{
		*head = a;
		a = a->next;
	}
	window_shopping(*head, a, b, 0);
}
/*
static void	list_show(t_list *sort)
{
	while (sort)
	{
		ft_putnbr_fd(sort->num, 1);
		sort = sort->next;
	}
	write(1, "\n", 1);
}
*/
static void	place_help(t_stack *a, t_list *sort, t_list *send)
{
	int		i;
	t_list	*curr;

	i = 0;
	curr = sort;
	while (curr)
	{
		((t_list *) curr->content)->num = i;
		curr = curr->next;
		i ++;
	}
	curr = send;
	i = 0;
	while (curr)
	{
		a->arr[i] = curr->num;
		curr = curr->next;
		i ++;
	}
//	list_show(send);
	free(send);
}

int	ps_placement(t_stack *a)
{
	int		i;
	int		size;
	t_list	*sort;
	t_list	*send;

	i = 0;
	size = a->top + 1;
	send = malloc((2 * size) * sizeof(t_list));//losing the malloc pointer LOLOLOLOOOL
	if (!send)
		return (1);
	sort = &send[size];
	while (i < size)
	{
		sort[i].next = &sort[i + 1];
		send[i].next = &send[i + 1];
		sort[i].num = a->arr[i];
		sort[i].content = &send[i];
		i ++;
	}
	sort[size - 1].next = NULL;
	send[size - 1].next = NULL;
	merge_sort(&sort);
	place_help(a, sort, send);
	return (0);
}
