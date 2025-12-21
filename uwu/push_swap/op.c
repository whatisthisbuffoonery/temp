#include "header_ps.h"

static void	rotate_help(t_stack *s, int mov)
{
	int	tmp;
	int	lim;
	int	i;

	if (s->top < 1)
		return ;
	i = s->top - 1;
	lim = -1;
	if (mov > 0)
	{
		lim = s->top + 1;
		i = 1;
	}
	tmp = s->arr[i - mov];
	while (i != lim)
	{
		s->arr[i - mov] = s->arr[i];
		i += mov;
	}
	s->arr[i - mov] = tmp;
}

void	ps_rotate(t_stack *a, t_stack *b, int flag)
{
	int	mov;

	mov = (flag & R) - !(flag & R);
	if (flag & R)
		write(1, "r", 1);
	if (flag & A && flag & B)
		write(1, "rr\n", 3);
	else if (flag & A)
		write(1, "ra\n", 3);
	else if (flag & B)
		write(1, "rb\n", 3);
	if (flag & A)
		rotate_help(a, mov);
	if (flag & B)
		rotate_help(b, mov);
}

void	ps_push(t_stack *a, t_stack *b, int flag)
{
	if (flag & A)
		write(1, "pa\n", 3);
	else if (flag & B)
		write(1, "pb\n", 3);
	if (flag & A && b->top >= 0)
	{
		a->top += 1;
		a->arr[a->top] = b->arr[b->top];
		b->top -= 1;
	}
	else if (flag & B && a->top >= 0)
	{
		b->top += 1;
		b->arr[b->top] = a->arr[a->top];
		a->top -= 1;
	}
}

void	ps_swap(t_stack *a, t_stack *b, int flag)
{
	int	tmp;
	int	top;

	if (flag & A && flag & B)
		write(1, "ss\n", 3);
	else if (flag & A)
		write(1, "sa\n", 3);
	else if (flag & B)
		write(1, "sb\n", 3);
	if (flag & A && a->top > 0)
	{
		top = a->top;
		tmp = a->arr[top];
		a->arr[top] = a->arr[top - 1];
		a->arr[top - 1] = tmp;
	}
	if (flag & B && b->top > 0)
	{
		top = b->top;
		tmp = b->arr[top];
		b->arr[top] = b->arr[top - 1];
		b->arr[top - 1] = tmp;
	}
}
