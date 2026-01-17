#ifndef HEADER_PS_H
# define HEADER_PS_H

# include "libft.h"
# include "get_next_line_bonus.h"

typedef struct s_stack
{
	int		*arr;
	int		top;
}			t_stack;

typedef struct s_iter
{
	int	i;
	int	curr;
	int	min;
	int	max;
	int	min_cost;
	int	max_cost;
	int	target;
}		t_iter;

typedef struct s_cost
{
	int	a;
	int	b;
	int	total;
}		t_cost;

int		ps_placement(t_stack *a);
int		init(int c, char **v, t_stack **a, t_stack **b);
int		sorted(t_stack *a, t_stack *b);
void	sort_three(t_stack *a, t_stack *b);

void	ps_rotate(t_stack *a, t_stack *b, int flag);
void	ps_push(t_stack *a, t_stack *b, int flag);
void	ps_swap(t_stack *a, t_stack *b, int flag);
void	ps_finish(t_stack *a, t_stack *b);
void	ps_write(char *a);

int		ps_num(int n, char *op);

int		find_a(t_stack *a, int src, t_iter num);
int		find_b(t_stack *b, int src, t_iter num);

void	ps_turk(t_stack *a, t_stack *b);
void	lsd_radix(t_stack *a, t_stack *b, int bit_max);
void	msd_radix(t_stack *a, t_stack *b, int bit_max, int runs);

int		ps_alien(unsigned char *in, unsigned char table[3][256]);
void	table_init(unsigned char table[3][256]);
void	ps_exec(t_stack *a, t_stack *b, unsigned char *in, int flag);

# define A 2
# define B 4
# define R 8

#endif
