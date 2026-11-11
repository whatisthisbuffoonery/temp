#include "ft_printf.h"

int	char_op(char src, int *len, t_write_head w)
{
	int	c;

	if (src == 'c')
		c = va_arg(*w.va, int);
	else
	{
		c = '%';
		w.sp.w_set = 0;
	}
	if (w.sp.w_set && w.sp.width <= 1)
		w.sp.w_set = 0;
	if ((w.sp.w_set && !w.sp.dash && fill_width(w, 1, 0))
		|| printf_repeat_write(w, c, 1)
		|| (w.sp.w_set && w.sp.dash && fill_width(w, 1, 0)))
		return (1);
	if (w.sp.w_set)
		*len += w.sp.width;
	else
		*len += 1;
	return (0);
}
