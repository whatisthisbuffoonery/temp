#include "header_ps.h"

void	ps_push(t_stack *a, t_stack *b, int flag);
void	ps_rotate(t_stack *a, t_stack *b, int flag);

static int	sorted(t_stack *a, t_stack *b)
{
	int	top;
	int	i;

	 if (b->top != -1)
		 return (0);
	 top = a->top;
	 i = 0;
	 while (i < top)
	 {
		 if (a->arr[i] < a->arr[i + 1])
			 return (0);
		 i ++;
	 }
	 return (1);
}

int	get_max(int max)
{
	int	i;

	i = 1;
	while (i * 2 <= max)
		i *= 2;
	return (i);
}

void	ps_show(t_stack *a)
{
	int	*arr = a->arr;
	int i = 0;
	int top = a->top;

	while (i <= top)
	{
		ft_putnbr_fd(arr[i], 1);
		write(1, " ", 1);
		i ++;
	}
	write(1, "\n", 1);
}

static int	push_back(t_stack *a, t_stack *b)
{
	int	i;
	int min;

	i = 0;
	min = 1;
	while (i <= b->top)
	{
		if (b->arr[i] == min)
			min ++;
		i ++;
	} 
	while (i >= min)
	{
		if (b->arr[b->top] < min)
			ps_rotate(a, b, B);
		else
			ps_push(a, b, A);
		i --;
	}
	return (min);
}

void	ps_sort(t_stack *a, t_stack *b, int max)
{
	int	bit;
	int	i;

	bit = 1;//get_max(max);
	//ps_show(a);
	//ft_putnbr_fd(bit, 1);
	//write(1, "\n", 1);
	while (bit <= max && !sorted(a, b))
	{
		i = a->top;
		while (i >= 0)
		{
		//	ps_show(a);
		//	ft_putnbr_fd(a->arr[a->top], 1);
		//	write(1, " | ", 3);
		//	ft_putnbr_fd(bit, 1);
		//	write(1, "\n", 1);
			if (!(a->arr[a->top] & bit))
				ps_push(a, b, B);
			else
				ps_rotate(a, b, A);//conditionally init R, i, mov, lim at start of each loop
			i --;
		}
//		ps_show(b);
//		while (b->top >= 0)
//			ps_push(a, b, A);
		write(1, "hm\n", 3);
		ps_show(b);
		if (b->top >= 0)
			push_back(a, b);
		ps_show(b);
		bit *= 2;
	}
	while (b->top >= 0)
		ps_push(a, b, A);
	ps_show(a);
}
