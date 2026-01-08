#include "header_ps.h"

int		sorted(t_stack *a, t_stack *b);
void	sort_three(t_stack *a);

void	show_cost(t_cost cost)
{
	write(1, "cost\na: ", 8);
	ft_putnbr_fd(cost.a, 1);
	write(1, "\nb: ", 4);
	ft_putnbr_fd(cost.b, 1);
	write(1, "\n", 1);
}

//4 > 3 2 1 0, a->top == 3


static t_cost	cost_overhead(t_stack *a, t_stack *b, t_cost rr)
{
	t_cost	ret;
	t_cost	rrr;

	rr.total = rr.a;
	if (rr.b > rr.a)
		rr.total = rr.b;
	rrr.a = 0 - (a->top - rr.a);//2 - 2 = 0
	rrr.b = 0 - (b->top - rr.b);//0 - 0 = 0
	rrr.total = 0 - rrr.a;
	if (rrr.b < rrr.a)
		rrr.total = 0 - rrr.b;
	ret.a = rr.a;
	if (rr.a > a->top / 2)
		ret.a = rrr.a;
	ret.b = rr.b;
	if (rr.b > b->top / 2)
		ret.b = rrr.b;
	ret.total = ABS(ret.a) + ABS(ret.b);
	show_cost(rr);
	show_cost(rrr);
	show_cost(ret);
	if (ret.total > rr.total)
		ret = rr;
	if (ret.total > rrr.total)
		ret = rrr;
	ret.total += 1;
	return (ret);
}

//start from top of each
//is 0 bigger than 0? no 2 - 0 = 2
//is 1 bigger than 0? yes 2 - 1 = 1
//a = i = 1
//min = 1

static int	find_a(t_stack *a, int src)
{
	int	i;
	int	min;
	int	max;

	i = 0;
	min = 0;
	max = INT_MAX;

	while (i <= a->top)


static t_cost	find_cost(t_stack *a, t_stack *b, int src, t_iter iter)//i need moar funcs to catch shit fuuuuu //phase out iter
{
	int		curr;
	t_cost	cost;
	t_iter	num;

	num = iter;
	write(1, "src: ", 5);
	ft_putnbr_fd(src, 1);
	write(1, "\n", 1);
	/*
	while (++num.i <= a->top)
	{
		curr = a->arr[a->top - num.i];
		if (curr > num.min && curr <= src)//biggest smaller //if no candidates, redo to find distance to top of smallest number
		{
			//ft_putnbr_fd(num.i, 1);
			cost.a = num.i;
			num.min = curr;
		}
	}
	num = iter;
	while (++num.i <= b->top)
	{
		curr = b->arr[b->top - num.i];
		if (curr < num.max && curr >= src)//smallest bigger //if not, push to bottom of biggest number
		{
			cost.b = num.i;
			num.max = curr;
		}
	}
	*/
	cost.a = find_a(a, src);
	cost.b = find_b(b, src);
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
		ps_rotate(a, b, A | (R * (mov < 0)));
		cost.a -= mov;
	}
	mov = (cost.b > 0) - (cost.b < 0);
	while (cost.b != 0)
	{
		ps_rotate(a, b, B | (R * (mov < 0)));
		cost.b -= mov;
	}
}


static void	heuristics(t_stack *a, t_stack *b, int bound, t_stack *src)
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
		show_cost(cost);
		if (cost.total <= i + 1)
			break ;
		if (bound == 5 && cost.total > i && i >= bound)
			bound = 10;
	}
	ps_rotate_overhead(a, b, cost, 0);
}

void	ps_turk(t_stack *a, t_stack *b, int min)
{
	int		bound;
	t_stack	*src;

	src = a;
	(void) min;
	while (a->top > 2)
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
}
