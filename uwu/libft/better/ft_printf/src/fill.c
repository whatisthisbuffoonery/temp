#include "ft_printf.h"

int	printf_max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

int	printf_repeat_write(t_write_head w, char c, int len)
{
	int	i;
	int	written;

	i = 0;
	while (i < len)
	{
		written = write(w.fd, &c, 1);
		if (written < 0)
		{
			if (errno == EINTR && !(w.flags | PF_EINTR))
				return (1);
			else if ((errno == EAGAIN || errno == EWOULDBLOCK)
				&& !(w.flags | PF_EAGAIN))
				return (1);
			written = 0;
		}
		i += written;
	}
	return (0);
}

int	fill_width(t_write_head w, int buflen, int p)
{
	char	c;
	int		len;

	len = w.sp.width - buflen - p;
	//printf("debug width... len:%d, width:%d, buflen:%d, p:%d\n", len, w.sp.width, buflen, p);
	if (len < 0)
		return (0);
	c = ' ';
	if (w.sp.zero)
		c = '0';
	return (printf_repeat_write(w, c, len));
}

int	fill_precision(t_write_head w, int p)
{
	if (p < 0)
		return (0);
	if (printf_repeat_write(w, '0', p))
		return (1);
	return (0);
}

int	fill_precision_hex(t_write_head w, int p)
{
	if (p < 0)
		return (0);
	return (printf_repeat_write(w, '0', p));
}
