#ifndef HEADER_PS_H
# define HEADER_PS_H

# include "libft.h"

typedef struct s_stack
{
	int	*arr;
	int	top;
}		t_stack;

typedef struct s_iter
{
	int	i;
	int	min;
	int	max;
}		t_iter;

typedef struct s_cost
{
	int	a;
	int	b;
	int	total;
}		t_cost;

void	turk(t_stack *a, t_stack *b, int min);
void	min_rotate(t_stack *a, t_stack *b);
void	ps_rotate(t_stack *a, t_stack *b, int flag);
void	ps_push(t_stack *a, t_stack *b, int flag);

# define A 2
# define B 4
# define R 8

# define ABS(x) ((x * (x > 0)) - (x * (x < 0)))

#endif
