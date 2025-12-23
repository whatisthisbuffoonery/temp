#include "header_ps.h"

/*
turk
	heu a/b		<<rotate, do not do logic
		find cost
*/

int	find_cost(t_stack *dst, int cmp, int *a, int *b)//which stack, which way.
{
	int	i;
	int	median;

	i = 0;
	while (dst->arr[dst->top - i] > cmp)
		i ++;

int	heuristics_to_b(t_stack *a, t_stack *b, int *bound)//I do have to make structs for "last n heuristics and their actions"
{
	int	i;
	int	tmp;
	int	min;
	int	a_cost;
	int	b_cost;

	i = 0;
	min = 99;
	dst = a;
	src = b->top;
	median = b->top - (b->top / 2);//consider making this do all the rotate overhead, 
	while (i < *bound)
	{
		tmp = ps_combine(i, find_cost(b, a->arr[a->top - i]));//max(ra, rb) + 1, single element comparison
		if (min > tmp)
			min = tmp;

void	turk(t_stack *a, t_stack *b)
{
	int	rotate;
	int	bound;

	bound = 5;//default
	while (!sorted(a, b))//catch total size < 5 somehow
	{
		while (a->top >= bound)
		{
			rotate = heuristics_to_b(a, b, &bound);//yay macros//let them handle tolerance
			while (rotate && a->top >= bound)
				ps_rotate(a, b, A);//ill let heuristics handle B and A|B
									//no rra on caller side, only first 5 or 10
			ps_push(a, b, B);
		}
		sort_smol(a);
		while (b->top >= bound)
		{
			rotate = heuristics_to_a(a, b, &bound);//conditionally set bound to 0 and stop the loop
			while (rotate && a->top >= bound)
				ps_rotate(a, b, B);
			ps_push(a, b, A);
		}
		if (bound)
			sort_smol(b);
	}
}
