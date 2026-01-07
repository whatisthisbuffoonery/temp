#include "header_ps.h"

void	ps_push(t_stack *a, t_stack *b, int flag);
void	ps_rotate(t_stack *a, t_stack *b, int flag);

int	sorted(t_stack *a, t_stack *b)
{
	int	top;
	int	i;

	 if (b && b->top != -1)
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

void	ps_show(t_stack *a)
{
	int	*arr = a->arr;
	int i = a->top;

	while (i >= 0)
	{
		ft_putnbr_fd(arr[i], 1);
		write(1, " ", 1);
		i --;
	}
	write(1, "\n", 1);
}

void probe(char *a, int n)
{
	int i = 0;
	int t = 1;

	while (a[i])
		i ++;
	write(1, a, i);
	if (n < 0)
	{
		write(1, "-", 1);
		n = 0 - n;
	}
	while (n / t > 9)
		t *= 10;
	while (t)
	{
		i = ((n / t) % 10) + '0';
		write(1, &i, 1);
		t /= 10;
	}
	write(1, "\n", 1);
}

int	find_max(t_stack *a)
{
	int	i;
	int	max;
	int	top;

	i = 0;
	max = 0;
	top = a->top;
	while (i <= top)
	{
		if (max < a->arr[i])
			max = a->arr[i];
		i ++;
	}
	i = 0;
	while (i <= top)
	{
		if (max == a->arr[i])
			max --;
		i ++;
	}
	return (max);
}

int	find_min(t_stack *b)
{
	int	i;
	int	min;
	int	top;

	i = 0;
	min = 0;
	top = b->top;
	while (i <= top)
	{
		if (b->arr[i] == min)
			min ++;
		i ++;
	}
	return (min - 1);
}

int	push_back_v2(t_stack *a, t_stack *b, int bit)
{
	int	i;
	int	push;
	int	min;
	int	push_two;

	min = find_min(b) - 1;
	i = b->top;
	push = 0;
	while (i >= 0)
	{
		if (b->arr[i] & bit && b->arr[i] > min)
			push ++;
		i --;
	}
	push_two = push;
	while (push)
	{
		if (b->arr[b->top] & bit && b->arr[b->top] > min)
		{
			push --;
			ps_push(a, b, A);
		}
		else
			ps_rotate(a, b, B);
	}
//	while (min >= 0 && b->arr[0] != 0)
//		ps_rotate(a, b, B);
	return (i);
}

int	ps_radix(t_stack *a, t_stack *b, int bit_max)
{
	int	bit;
	int	i;
	int	push;

	bit = 1;
	(void) push;
	while (bit <= bit_max && !sorted(a, b))
	{
		i = a->top - min_rotate(a, b, bit);//rotate b here!! //guard min urself
		while (i >= 0)
		{
			if (!(a->arr[a->top] & bit))
				ps_push(a, b, B);
			else
				ps_rotate(a, b, A);
			i --;
		}
		bit *= 2;
		if (b->top >= 0 && bit <= bit_max)
			push_back_v2(a, b, bit);
	}
	while (b->top >= 0)
		ps_push(a, b, A);
//	ps_show(a);
	//ps_show(b);
	return (find_min(b));
}
