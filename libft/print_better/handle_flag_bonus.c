#include "header_mand.h"
//flag null check maybe done before this//nah the init will do it

static char	*handle_flag_init(size_t, size, t_queue, *q, int *len)//plan to set some flags to 0
{
	char	a;

	a = q->arg;
	len = size;
	if (len < q->flags->precision)
		len = q->flags->precision;
	if (len < q->flags->width)
		len = q->flags->width;
	len += (q->flags->plus_space > 0);
	ret = malloc(len * sizeof(char));
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
	return (ret);
}

static void	width_help

char	*handle_flag(size_t size, t_queue *q, int *index)//I just have to take out 0x first dont i//or pass the prefix flag in here, that works
{
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
	ret[len - 1] = '\0';
	if (width > size && width > prec)
	{
		start = 0;
		if (q->flags->minus_space == '-')
			
