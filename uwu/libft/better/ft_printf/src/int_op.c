#include "ft_printf.h"

//buffer length needed to represent 128bit numbner in binary is 128 + \r\n\0 = 131
static void	signed_buf(char *buf, int *index, intmax_t src, t_write_head *w)
{
	int			offset;
	int			i;
	uint32_t	n;

	/*if sizeof(l or ll) != 4 (32/8)...delegate to 64bit*/
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
		*p = sp->precision - *buflen;
	if (*p < 1)
	{
		*p = 0;
		sp->p_set = 0;
	}
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
	int			i;
	int			buflen;
	int			p;
	intmax_t	n;
	int			prefix;

	n = va_arg(*w.va, int);//subject to change due to length modifiers: hh is char, h is short, l is long, ll is long long
	signed_buf(w.buf, &i, n /*va_next(*w.va, int)*/, &w);
	prefix = (w.minus || w.sp.plus || w.sp.space);
	buflen = NUM_BUFFER - i;//-1 on the buffer for 0 index, zzzzzzz
	set_length(&w.sp, &buflen, &p, n);
	if ((w.sp.zero && signed_prefix(w))
		|| (w.sp.w_set && !w.sp.dash && fill_width(w, buflen + prefix, p))
		|| (!w.sp.zero && signed_prefix(w))
		|| (p > 0 && fill_precision(w, p))
		|| printf_write(w, &w.buf[i], buflen)
		|| (w.sp.w_set && w.sp.dash && fill_width(w, buflen + prefix, p)))
		return (1);
	*len += printf_max(w.sp.width, buflen + p + prefix);
	return (0);
}
