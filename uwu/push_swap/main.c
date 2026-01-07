#include "header_ps.h"

void	ps_show(t_stack *a);
int		init(int c, char **v, t_stack **a, t_stack **b);
int		ps_placement(t_stack *a);
int		sorted(t_stack *a, t_stack *b);
void	ps_radix(t_stack *a, t_stack *b, int max);
void	ps_turk(t_stack *a, t_stack *b, int min);
void	ps_swap(t_stack *a, t_stack *b, int flags);

void	min_rotate(t_stack *a, t_stack *b)
{
	int	i;
	int	median;

	i = 0;
	median = a->top / 2;
	while (i <= a->top && a->arr[a->top - i] != 0)
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

static void	ps_clear(t_stack *a, t_stack *b)
{
	if (a)
		free(a->arr);
	if (b)
		free(b->arr);
	free(a);
	free(b);
}
//123
//132
//213
//231
//321
//312

// go thru turk again and make sort 5 //push lowest 2 to b
// pls handle rr and rrr for radix, use another func
//make radix not loop thru the min section

void	sort_three(t_stack *a, t_stack *b)
{
	if (a->arr[2] == 0)
		ps_rotate(a, b, A);
	else if (a->arr[1] == 0)
		ps_rotate(a, b, A | R);
	if (a->arr[2] > a->arr[1])
		ps_swap(a, b, A);
	ps_rotate(a, b, A | R);
}

void	ps_sort(t_stack *a, t_stack *b, int max)
{
	/*
	int	bit_max;
	int	min;

	bit_max = 0;
	min = 0;
	if (sorted(a, b))
		return ;
	if (max == 1)
	{
		if (a->arr[1] > a->arr[0])
			ps_swap(a, b, A);
		return ;
	}
	if (max >= 100)
		bit_max = 4;
	if (max >= 500)
		bit_max = 8;
	if (bit_max)
		min = ps_radix(a, b, bit_max);
	if (min < 3)
		min = 3;
	if (!sorted(a, b))
		ps_turk(a, b, min);
	min_rotate(a, b);
	*/
	ps_radix(a, b, max);
//	ps_turk(a, b, 3);
}

void	ps_fuck(t_stack *a, t_stack *b)
{
	write(1, "a: ", 3);
	ft_putnbr_fd(a->top, 1);
	write(1, "\nb: ", 4);
	ft_putnbr_fd(b->top, 1);
	write(1, "\n", 1);
}

int	main(int c, char **v)
{
	t_stack	*a;
	t_stack	*b;

	a = NULL;
	b = NULL;
	if (c < 2)//has to accept 1 arg now
		return (0);//i wonder
	c --;
	//ft_putnbr_fd(c, 1);
	//write(1, " start\n", 6);
	if (!init(c, &v[1], &a, &b) && !ps_placement(a))
	{
	//	ps_show(a);
	//	ps_fuck(a, b);
		ps_sort(a, b, a->top);
	}
	else
		write(2, "Error\n", 6);//not visible on output
	ps_clear(a, b);
}
