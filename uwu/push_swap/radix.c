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

static int	find_min(t_stack *b)//, int *prev_bound)
{
	int	i;
	int	min;
	int	top;
//	int	start_1;

	i = 0;
//	start_1 = 0;
	min = 0;
	top = b->top;
	while (i <= top)
	{
		if (b->arr[i] == min)
		{
//			if (!start_1)
//				start_1 = i;
			min ++;
		}
		i ++;
	}
//	i = 0;
//	while (i < start_1)
//	{
//		if (b->arr[i] == min)
//			min ++;
//		i ++;
//	}
	return (min);
}//propose a more heavy handed algo

void	push_back(t_stack *a, t_stack *b)//, int *prev_bound)
{
	int min;

//	probe("start: ", b->arr[i]);
//	probe("i: ", i);
//	probe("top: ", b->top);
	min = find_min(b) - 1;
//	probe("min: ", min);
	while (b->top > min)
	{
		if (b->arr[b->top] <= min)
		{
			ps_rotate(a, b, B);
//			ps_show(b);
		}
		else
			ps_push(a, b, A);
	}
//	probe("top: ", b->top);
	while (min > 0 && b->arr[0] != 1)
		ps_rotate(a, b, B);
}

int	push_back_v2(t_stack *a, t_stack *b, int bit)//pull min into this too
{
	int	i;
	int	min;

	min = find_min(b) - 1;
	i = b->top;
	while (i >= 0)
	{
		if (b->arr[b->top] & bit && b->arr[b->top] > min)
			ps_push(a, b, A);
		else
			ps_rotate(a, b, B);
		i --;
	}
	min_rotate(a, b);
	return (i);
}

int	ps_radix(t_stack *a, t_stack *b, int max)
{
	int	bit;
	int	share;
	int	i;

	share = 0;
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
				ps_rotate(a, b, A);// | (B && (share-- > 0)));//conditionally init R, i, mov, lim at start of each loop
			i --;
		}
//		ps_show(b);
//		while (b->top >= 0)
//			ps_push(a, b, A);
//		write(1, "hm\n", 3);
//		ps_show(b);
//		write(1, "start\n", 6);
//		ps_show(b);
		bit *= 2;
		if (b->top >= 0 && bit <= max)
			push_back_v2(a, b, bit);//, &prev);
//		write(1, "end\n", 4);
//		ps_show(b);
	}
//	while (b->top >= 0)
//		ps_push(a, b, A);
	ps_show(a);
	return (find_min(b));
}
