#include "header_ps.h"

static int	dup_check(int *arr, int c)
{
	int	i;
	int	k;

	i = -1;
	while (++i < c)
	{
		k = i;
		while (++k < c)
		{
			if (arr[i] == arr[k])
				return ((free(arr)), 1);
		}
	}
	return (0);
}

static int	bounds_check(char *v)
{
	int	i;
	int	a;
	int	tmp;

	i = 0;
	a = 0;
	while (v[i])
	{
		tmp = a * 10;
		if (a && tmp <= a)
			return (1);
		a = tmp;
		a += v[i] + '0';
		i ++;
	}
	return (0);
}

static int	validate(int c, char **v, int **arr)
{
	int		i;
	int		k;
	int		count;
	char	a;

	count = c;
	*arr = malloc(c * sizeof(int));
	if (!*arr)
		return (1);
	i = -1;
	while (++i < c)
	{
		k = -1;
		if (v[i][0] == '-')
			k ++;
		while (v[i][++k])
		{
			a = v[i][k];
			if (a < '0' || a > '9')
				return ((free(*arr)), 1);
		}
		if (bounds_check(v[i]))
			return ((free(*arr)), 1);
		(*arr)[--count] = ft_atoi(v[i]);
	}
	return (dup_check(*arr, c));
}

int	init(int c, char **v, t_stack **a, t_stack **b)
{
	int	*arr;

	if (validate(c, v, &arr))
		return (1);
	*a = malloc(sizeof(t_stack));
	*b = malloc(sizeof(t_stack));
	if (!*a || !*b)
		return ((free(arr)), 1);
	(*a)->arr = arr;
	(*b)->arr = malloc(c * sizeof(int));
	if (!(*b)->arr)
		return (1);
	(*a)->top = c - 1;
	(*b)->top = -1;
	return (0);
}
/*
int runs_init(t_runs **runs, int size)
{
	*runs = malloc(sizeof(t_runs));
	if (!*runs)
		return (1);
	(*runs)->start = malloc(size * sizeof(int));
	(*runs)->len = malloc(size * sizeof(int));
	if (!(*runs)->start || !(*runs)->len)
		return (1);
	return (0);
}
*/