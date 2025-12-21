#ifndef HEADER_PS_H
# define HEADER_PS_H

# include "libft.h"

typedef struct s_stack
{
	int	*arr;
	int	top;
}		t_stack;

typedef struct s_runs
{
	int	*start;
	int	*len;
}		t_runs;

# define A 2
# define B 4
# define R 8

#endif
