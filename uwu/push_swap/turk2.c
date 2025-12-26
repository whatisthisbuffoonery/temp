#include "header.ps"

void	turk_finalise(t_stack *a, t_stack *b)
{
	int	i;
	int	median;

	i = 0;
	median = a->top / 2;
	while (a->arr[a->top - i] != 0)
		i ++;
	if (i > median)
	{
		while (i <= a->top)
			ps_rotate(a, b, A | R);
		i ++;
	}
	else
	{
		while (i > 0)
			ps_rotate(a, b, A);
		i --;
	}
}
