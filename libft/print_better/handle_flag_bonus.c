#include "header_mand.h"
//flag null check maybe done before this//nah the init will do it

static int muh_max(int a, int b, int c)
{
	if (a < b)
		a = b;
	if (a < c)
		a = c;
	return (a);
}

void	probe(char *a, char flag)
{
	int i = 0;
	while (a[i])
		i ++;
	write(1, a, i);
	write(1, &flag, 1);
	write(1, "'\n", 2);
}

static char	*handle_flag_init(size_t size, t_queue *q, int *len)
{
	char	a;
	char	*ret;

	a = q->arg;
	*len = size;
	if (q->flags)
	{
		if (a != 'x' && a != 'X')
			q->flags->hex = 0;//that uint malloc doesnt look good
		if (a != 'd' && a != 'i')
			q->flags->plus_space = 0;
		if ((a == 'c' || a == 's' || a == 'p') && q->flags->minus_zero == '0')
			q->flags->minus_zero = 0;
		if (a == 'c')
			q->flags->precision = 0;
		q->flags->precision += 2 * (q->flags->hex > 0);
		q->flags->precision += (q->flags->plus_space > 0);//same logic as 0x prefix
		if (q->flags->precision < 0)
			q->flags->precision = size;
		*len = muh_max(size, q->flags->precision, q->flags->width);
	}
	ret = malloc((*len + 1) * sizeof(char));
	if (ret)
		ret[*len] = '\0';
	return (ret);
}

static void	width_fill(char *ret, int start, int width, char flag)
{
	char	c;

//	probe("my flag is '", flag);
	c = ' ';
	if (flag == '0')
		c = '0';
	while (start < width)
		ret[start++] = c;
}//can be compressed for a func slot, or toss some more lines in here

int	set_index(int size, int prec, int width, char flag)
{
	int	i;

	if (flag == '-')
		i = prec - size;
	else
		i = muh_max(width, prec, 0) - size;
	if (i < 0)
		i = 0;
	return (i);
}

void yeet_it(int len, int index)
{
	write(1, "len: ", 5);
	ft_putnbr_fd(len, 1);
	write(1, "\nindex: ", 8);
	ft_putnbr_fd(index, 1);
	write(1, "\n\n", 2);
}

char	*handle_flag(size_t size, t_queue *q, int *index)//I just have to take out 0x first dont i//or pass the prefix flag in here, that works
{//OR uint op sees the set index, and shifts two padding chars forward to fit 0x, helper can do it.
	//int op should do flag && !plus_space in calculations. And use a helper to fill flag sign.
	//if flag '-' do not shift 2 padding bytes, just eat the last two for 0x.
	//account for padding == 1
	//tell the other funcs to not include null terminator, or idk, do?
	//my index is fucked hang on
	char	*ret;
	int		len;
	int		width;
	int		prec;
	int		start;

	ret = handle_flag_init(size, q, &len);//must edit %d and %i to write -/+ to ret[0]
	if (!ret || !q->flags)//bandaids so good
		return ((*index = 0), ret);
	width = q->flags->width;
	prec = q->flags->precision;
	ft_memset(ret, '0', len);//fuck cares about precision check
	*index = set_index(size, prec, width, q->flags->minus_zero);
	if (width > muh_max(size, prec, 0))
	{
		start = 0;
		if (q->flags->minus_zero == '-')
			start = muh_max(size, prec, 0);
		width -= muh_max(size, prec, 0) * !start;
		width_fill(ret, start, width, q->flags->minus_zero);
	}
//	yeet_it(len, *index);
	//ret[len - 1] = '\0';//terminator now lives in init
	return (ret);
}

int	valid_cond_printf(const char *format, char *type, char *flag, int *index)//line up the names after
{//duplicate flags allowed ig
	int	i;

	i = *index;
	if (format[i] == '%')
		return (0);
	while (flag[(unsigned char) format[i]])//put hex back in damn you
		i ++;
	while (format[i] >= '0' && format[i] <= '9')
		i ++;
	if (format[i] == '.')
	{
		i ++;
		while (format[i] >= '0' && format[i] <= '9')
			i ++;
	}
	*index = i;
	return (!type[(unsigned char) format[i]]);
}
