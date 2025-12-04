#include "header_mand.h"
//flag null check maybe done before this//nah the init will do it

static char	*handle_flag_init(size_t, size, t_queue, *q, int *len)//plan to set some flags to 0
{
	char	a;

	a = q->arg;
	len = size;
	if (a != 'x' && a != 'X')
		q->flags->hex = 0;//that uint malloc doesnt look good
	if (a != 'd' && a != 'i')
		a->flags->plus_space = 0;
	if (a == 'c' || a == 's')
	{
		if (a->flags->minus_zero == '0')
			a->flags->minus_zero = 0;
		a->flags->precision = 0;
	}
	if (len < q->flags->precision)
		len = q->flags->precision;
	if (len < q->flags->width)
		len = q->flags->width;
	len += (q->flags->plus_space > 0);
	ret = malloc(len * sizeof(char));

	return (ret);
}

static int muh_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static void	width_fill(char *ret, int start, int width, char flag)
{
	char	c;
	int		max;

	c = ' ';
	if (flag == '0')
		c = '0';
	max = width;
	if (!start)
		max = width - start;
	while (start < max)
		ret[start++] = c;
}

char	*handle_flag(size_t size, t_queue *q, int *index)//I just have to take out 0x first dont i//or pass the prefix flag in here, that works
{//OR uint op sees the set index, and shifts two padding chars forward to fit 0x, helper can do it.
	//int op should do flag && !plus_space in calculations. And use a helper to fill flag sign.
	//if flag '-' do not shift 2 padding bytes, just eat the last two for 0x.
	//account for padding == 1
	char	*ret;
	int		len;
	int		width;
	int		prec;
	int		start;

	ret = handle_flag_init(size, q, &len);//must edit %d and %i to write -/+ to ret[0]
	if (!ret)
		return (NULL);
	width = q->flags->width;
	prec = q->flags->precision;
	ft_memset(ret, '0', len);//fuck cares about precision check
	if (width > muh_max(size, prec))
	{
		start = 0;
		if (q->flags->minus_space == '-')
			start = muh_max(size, prec);
		width_fill(ret, start, width - (muh_max(size, prec) * !start), q->flags->minus_zero);
	}
	*index = muh_max(width, prec) - size;
	if (*index < 0)
		*index = 0;
	ret[len - 1] = '\0';
	return (ret);
}
