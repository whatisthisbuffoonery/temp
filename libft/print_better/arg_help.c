#include "header_mand.h"

int	prec_help(char *ret, t_queue *q, int n)
{
	int	width;

	if (!q->flags || n)
		return (0);
	if (!q->flags->precision && q->flags->precision_set)
	{
		width = q->flags->width;
		width += (q->flags->plus_space == '+') * !width
		ft_memset(ret, ' ', width);
		ret[width] = '\0';
		if (q->flags->plus_space == '+')
			ret[width - 1] = '+';
		return (1);
	}
	return (0);
}

int	uint_help(char *ret, int flag, int *i, char arg)
{
	int	k;

	if (!ret)
		return (1);
	if (flag)
	{
		k = 0;
		while (ret[k] == ' ' && k < *i)
			k ++;
		ret[k] = '0';
		ret[k + 1] = 'x';
		if (arg == 'X')
			ret[k + 1] = 'X';
		*i += flag;//handle_flag placed it after flag requirements, used to be i = flag
	}
	return (0);
}
//the above mostly works, but for bonus we may want to place the 0x earlier
//walk k bytes until either encountering a 0 or catching up to *i

//model: *i = max(width, prec) minus size, min 0
//if flag, follow the above to place prefix and then add 2 to *i regardless what the other circumstances are
//if !flag, do nothing

void	int_help(char *ret, int flag, t_queue *q, int *index)
{
	int	i;
	int	c;
	int	has_sign;

	i = 0;
	has_sign = (q->flags && q->flags->plus_space > 0);
	if (flag || has_sign)
	{
		while (i < *index && ret[i] == ' ')
			i ++;
	}
	if (flag)
		ret[i] = '-';
	else if (has_sign)
	{
		c = q->flags->plus_space;
		ret[i] = c;
	}
	if (flag || has_sign)
		*index += 1;
}
