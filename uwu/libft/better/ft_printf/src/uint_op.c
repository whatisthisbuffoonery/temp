#include "ft_printf.h"

//buffer length needed to represent 128bit numbner in binary is 128 + \r\n\0 = 131
static void	unsigned_buf(char *buf, int *index, unsigned int n, t_write_head *w)
{
	int	offset;
	int	i;

	offset = NUM_BUFFER - 1;
	i = 0;
	while (offset >= i && (n || !i))
	{
		buf[offset - i] = (n % 10) + '0';
		n /= 10;
		i ++;
	}
	if (w->sp.space)
		buf[offset - i] = ' ';
	else if (w->sp.plus)
		buf[offset - i] = '+';
	else
		i -= 1;
	*index = offset - i;
}

static void	set_length(t_pf_specifiers *sp, int *buflen, int *p, unsigned int n)
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

//width finder thing, should use different functions for signed, unsigned, and hex numbers
int	uint_op(int *len, t_write_head w)
{
	int			i;
	int			buflen;
	int			p;
	uintmax_t	n;

	n = va_arg(*w.va, unsigned int);//subject to change due to length modifiers: hh is char, h is short, l is long, ll is long long
	unsigned_buf(w.buf, &i, n /*va_next(*w.va, int)*/, &w);
	buflen = NUM_BUFFER - i;
	set_length(&w.sp, &buflen, &p, n);
	if ((w.sp.w_set && !w.sp.dash && fill_width(w, buflen, p))
		|| (p && fill_precision(w, p))
		|| printf_write(w, &w.buf[i], buflen)
		|| (w.sp.w_set && w.sp.dash && fill_width(w, buflen, p)))
		return (1);
	*len += printf_max(w.sp.width, buflen + p);
	return (0);
}
