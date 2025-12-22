#include "header_ps.h"

int		init(int c, char **v, t_stack **a, t_stack **b);
int	ps_placement(t_stack *a);
void	ps_sort(t_stack *a, t_stack *b, int max);

static void	ps_clear(t_stack *a, t_stack *b)//, t_runs *runs)
{
	if (a && a->arr)
		free(a->arr);
	if (b && b->arr)
		free(b->arr);
//	if (runs && runs->start)
//		free(runs->start);
//	if (runs && runs->len)
//		free(runs->len);
	if (a)
		free(a);
	if (b)
		free(b);
//	if (runs)
//		free(runs);
}

int	main(int c, char **v)
{
	t_stack	*a;
	t_stack	*b;
//	t_runs	*runs;

	a = NULL;
	b = NULL;
	//ft_putnbr_fd(c, 1);
//	write(1, "\n", 1);
	if (c < 3)
		return (0);//i wonder
	c --;
	if (!init(c, v + 1, &a, &b) && !ps_placement(a))// && !runs_init(&runs))
		ps_sort(a, b, c - 1);//c minus two, one for argv[0] and the other for 0 index
	else
		write(2, "Error\n", 6);
	ps_clear(a, b);
}
