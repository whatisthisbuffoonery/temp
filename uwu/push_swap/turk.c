#include "header_ps.h"

static t_cost	cost_overhead(t_stack *a, t_stack *b, t_cost rr)
{
	t_cost	ret;
	t_cost	rrr;

	rr.total = rr.a;
	if (rr.b > rr.a)
		rr.total = rr.b;
	rrr.a = 0 - (a->top - rr.a);
	rrr.b = 0 - (b->top - rr.b);
	rrr.total = 0 - rrr.a;
	if (rrr.b < rrr.a)
		rrr.total = 0 - rrr.b;
	ret.a = rr.a;
	if (rr.a > a->total / 2)
		ret.a = rrr.a;
	ret.b = rr.b;
	if (rr.b > b->total / 2)
		ret.b = rrr.b;
	ret.total = ABS(ret.a) + ABS(ret.b);
	if (ret.total > rr.total)
		ret = rr;
	if (ret.total > rrr.total)
		ret = rrr;
	ret.total += 1;
	return (ret);
}

static t_cost	find_cost(t_stack *a, t_stack *b, int src, t_iter iter)
{
	int		curr;
	t_cost	cost;
	t_iter	num;

	num = iter;
	while (++num.i <= a->top)
	{
		curr = a->arr[a->top - num.i];
		if (curr > num.min && curr <= src)//biggest smaller
		{
			cost.a = num.i;
			num.min = curr;
		}
	}
	num = iter;
	while (++num.i <= b->top)
	{
		curr = b->arr[b->top - num.i];
		if (curr < num.max && curr >= src)//smallest bigger
		{
			cost.b = num.i;
			num.max = curr;
		}
	}
	return (cost_overhead(a, b, cost));
}

static void	ps_rotate_overhead(t_stack *a, t_stack *b, t_cost cost, int mov)
{
	while(cost.a > 0 && cost.b > 0)
	{
		cost.a --;
		cost.b --;
		ps_rotate(a, b, A | B);
	}
	while (cost.a < 0 && cost.b < 0)
	{
		cost.a ++;
		cost.b ++;
		ps_rotate(a, b, A | B | R);
	}
	mov = (cost.a > 0) - (cost.a < 0);
	while (cost.a != 0)
	{
		ps_rotate(a, b, A | (R * (mov > 0)));
		cost.a -= mov;
	}
	mov = (cost.b > 0) - (cost.b < 0);
	while (cost.b != 0)
	{
		ps_rotate(a, b, B | (R * (mov > 0)));
		cost.b -= mov;
	}
}

int	heuristics(t_stack *a, t_stack *b, int bound, t_stack *src;)
{
	int		i;
	int		src_num;
	t_cost	tmp;
	t_cost	cost;
	t_iter	iter;

	i = 0;
	cost.total = INT_MAX;
	iter.i = -1;
	iter.min = 0;
	iter.max = INT_MAX;
	while (i < bound)
	{
		src_num = src->arr[src->top - i];
		tmp = find_cost(a, b, src_num, iter);
		if (tmp.total < cost.total)
			cost = tmp;
		i ++;
		if (cost.total <= i + 1)
			break ;
		if (bound == 5 && cost.total > i && i >= bound)
			bound = 10;
	}
	ps_rotate_overhead(a, b, cost);
}

void	turk(t_stack *a, t_stack *b, int min)//oh brother i have to incorporate the previous min
{
	int		bound;
	t_stack	*src;

	src = a;
	while (a->top > min)
	{
		bound = 5;
		if (a->top < bound)
			bound = a->top + 1;
		heuristics(a, b, bound, src);
		ps_push(a, b, B);
	}
	if (!sorted(a, 0))
		sort_three(a);
	src = b;
	while (b->top >= 0)
	{
		bound = 5;
		if (b->top < bound)
			bound = b->top + 1;
		heuristics(a, b, bound, src);
		ps_push(a, b, A);
	}
	turk_finalise(a, b);
}
