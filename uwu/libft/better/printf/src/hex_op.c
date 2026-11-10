#include "ft_printf.h"

int	str_op(int *len, t_write_head w, char *str);

//buffer length needed to represent 128bit numbner in binary is 128 + \r\n\0 = 131
static void	hex_buf(char *buf, int *index, uintptr_t n, char c)
{
	int		offset;
	int		i;
	char	a;

	offset = NUM_BUFFER - 1;
	i = 0;
	while (offset >= i && (n || !i))
	{
		a = (n % 16);
		if (a < 10)
			a += '0';
		else if (c == 'X')
			a += 'A' - 10;
		else
			a += 'a' - 10;
		buf[offset - i] = a;
		n /= 16;
		i ++;
	}
	i -= 1;
	*index = offset - i;
}

static void	set_length(t_pf_specifiers *sp, int *buflen, int *p, uintptr_t n)
{
	*p = 0;
	if (sp->p_set && !sp->precision)
	{
		sp->p_set = 0;
		if (!n)
		{
			sp->hex = 0;
			*buflen = 0;
		}
	}
	else if (sp->p_set)
		*p = sp->precision - *buflen;//no dot
	if (*p < 1)
		sp->p_set = 0;
	if (*buflen && sp->hex)
		*buflen += 2;
	if (sp->w_set && *buflen + *p >= sp->width)
		sp->w_set = 0;
}

static int	resolve_arg(uintptr_t *n, t_write_head *w, char c)
{
	if (c != 'p')
	{
		*n = va_arg(*w->va, unsigned int);
		return (0);
	}
	w->sp.hex = 1;
	w->sp.zero = 0;
	*n = va_arg(*w->va, uintptr_t);
	return (!*n);
}

//width finder thing, should use different functions for signed, unsigned, and hex numbers
int	hex_op(char c, int *len, t_write_head w)
{
	int			i;
	int			buflen;
	int			p;
	uintptr_t	n;
	char		*prefix;

	if (resolve_arg(&n, &w, c))//subject to change due to length modifiers: hh is char, h is short, l is long, ll is long long
		return ((w.sp.p_set = 0), str_op(len, w, "(nil)"));
	hex_buf(w.buf, &i, n /*va_next(*w.va, int)*/, c);
	buflen = NUM_BUFFER - i;
	set_length(&w.sp, &buflen, &p, n);
	prefix = "0x";
	if (c == 'X')
		prefix = "0X";
	//printf("hex debug... buflen: %d\n", buflen);
	if ((w.sp.w_set && !w.sp.dash && fill_width(w, buflen, p))
		|| (w.sp.hex && printf_write(w, prefix, 2))
		|| (p && fill_precision_hex(w, p))
		|| printf_write(w, &w.buf[i], buflen - (2 * w.sp.hex))//yup this goes last now
		|| (w.sp.w_set && w.sp.dash && fill_width(w, buflen, p)))
		return (1);
	if (w.sp.w_set)
		*len += w.sp.width;
	else
		*len += buflen + p;
	return (0);
}
