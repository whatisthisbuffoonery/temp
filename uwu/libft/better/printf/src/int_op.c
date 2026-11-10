#include "ft_printf.h"

//buffer length needed to represent 128bit numbner in binary is 128 + \r\n\0 = 131
static void	signed_buf(char *buf, int *index, int src, t_write_head *w)
{
	int				offset;
	int				i;
	unsigned int	n;

	offset = NUM_BUFFER - 1;
	i = 0;
	w->minus = (src < 0);
	n = src;
	if (w->minus)
		n = 0u - n;
	while (offset >= i && (n || !i))
	{
		buf[offset - i] = (n % 10) + '0';
		n /= 10;
		i ++;
	}
	/*
	if (w->minus)
		buf[offset - i] = '-';
	else if (w->sp.space)
		buf[offset - i] = ' ';
	else if (w->sp.plus)
		buf[offset - i] = '+';
	*/
	//else
	i -= 1;
	*index = offset - i;
	//printf("debug index:%d\n", *index);
}

static void	set_length(t_pf_specifiers *sp, int *buflen, int *p, int n)
{
	*p = 0;
	if (sp->p_set && !sp->precision)
	{
		sp->p_set = 0;
		if (!n)
			*buflen = 0;
	}
	else if (sp->p_set)
		*p = sp->precision + 1;
	if (sp->w_set && *buflen + *p >= sp->width)
		sp->w_set = 0;
}

int	signed_prefix(t_write_head w)
{
	char	c;

	if (w.minus)
		c = '-';
	else if (w.sp.plus)
		c = '+';
	else if (w.sp.space)
		c = ' ';
	else
		return (0);
	return (printf_repeat_write(w, c, 1));
}

//width finder thing, should use different functions for signed, unsigned, and hex numbers
int	int_op(int *len, t_write_head w)
{
	int		i;
	int		buflen;
	int		p;
	int		n;

	n = va_arg(*w.va, int);//subject to change due to length modifiers: hh is char, h is short, l is long, ll is long long
	signed_buf(w.buf, &i, n /*va_next(*w.va, int)*/, &w);
	buflen = NUM_BUFFER - (i - (w.minus || w.sp.plus || w.sp.space));//-1 on the buffer for 0 index, zzzzzzz
	set_length(&w.sp, &buflen, &p, n);
	if ((w.sp.zero && signed_prefix(w))
		|| (w.sp.w_set && !w.sp.dash && fill_width(w, buflen, p))
		|| (!w.sp.zero && signed_prefix(w))
		|| printf_write(w, &w.buf[i], buflen)
		|| (p && fill_precision(w, p))
		|| (w.sp.w_set && w.sp.dash && fill_width(w, buflen, p)))
		return (1);
	if (w.sp.w_set)
		*len += w.sp.width;
	else
		*len += buflen + p;
	return (0);
}
