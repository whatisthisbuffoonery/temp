#include "ft_printf.h"

int	str_op(int *len, t_write_head w, const char *str)
{
	int		buflen;

	if (!str)
	{
		str = "(null)";//why oh why does gnu let you truncate this fallback
		if (w.sp.p_set && w.sp.precision < 6)
			str = "";
	}
	buflen = ft_strlen(str);
	w.sp.zero = 0;
	//printf("debug flags... precision>> %d:%d\n", w.sp.p_set, w.sp.precision);
	if (w.sp.p_set && w.sp.precision < buflen)
		buflen = w.sp.precision;
	if (w.sp.w_set && w.sp.width <= buflen)
		w.sp.w_set = 0;
	if ((w.sp.w_set && !w.sp.dash && fill_width(w, buflen, 0))
		|| printf_write(w, str, buflen)
		|| (w.sp.w_set && w.sp.dash && fill_width(w, buflen, 0)))
		return (1);
	if (w.sp.w_set)
		*len += w.sp.width;
	else
		*len += buflen;
	return (0);
}
