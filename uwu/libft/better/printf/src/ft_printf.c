#include "ft_printf.h"

int	printf_symbol(const char **format, int *len, t_write_head w);

int	printf_exit(int n, va_list *va)
{
	va_end(*va);
	return (n);
}

int	printf_fd(int n)
{
	static int	fd;

	if (n != PRINTF_PROBE)
		fd = n;
	if (fd < 1)
		fd = 1;
	return (fd);
}

//set errno flags to 1 to ignore them
int	printf_flags(int n)
{
	static int	flags;
	static int	setup;

	if (!setup)
		flags = PF_EAGAIN | PF_EINTR;
	setup = 1;
	if (n != PRINTF_PROBE)
	{
		flags = 0;
		if (n == EAGAIN || n == EWOULDBLOCK)
			flags |= PF_EAGAIN;
		else if (n == EINTR)
			flags |= PF_EINTR;
	}
	return (flags);
}

int	printf_write(t_write_head w, const char *str, int len)
{
	int	i;
	int	written;

	i = 0;
	while (i < len)
	{
		written = write(w.fd, &str[i], len - i);
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

//posix standard defines I will not be multitasking normal use case and grabbing positional args %2$d
//that will be a separate implementation
int	ft_printf(const char *format, ...)
{
	int				i;
	int				len;
	va_list			va;
	char			buf[NUM_BUFFER];
	t_write_head	w;

	va_start(va, format);
	w.fd = printf_fd(PRINTF_PROBE);
	w.flags = printf_flags(PRINTF_PROBE);
	w.va = &va;
	w.buf = buf;
	len = 0;
	while (*format)
	{
		i = 0;
		while (format[i] && format[i] != '%')
			i ++;
		if (printf_write(w, format, i) < 0)
			return (printf_exit(-1, &va));
		len += i;
		format = &format[i];
		if (*format == '%' && printf_symbol(&format, &len, w))
			return (printf_exit(-1, &va));
	}
	return (printf_exit(len, &va));
}
