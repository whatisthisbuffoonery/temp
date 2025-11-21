#include "ft_printf.h"

static void	tabler(char a[], int *int1, int *int2)//relegate this to just d, i, x, X, u
{
	int	i;

	i = 0;
	*int1 = 0;
	*int2 = 0;
	while (i < 256)
		a[i++] = 0;
	a['c'] = 1;
	a['s'] = 1;
	a['p'] = 1;
	a['i'] = 1;
	a['u'] = 1;
	a['x'] = 1;
	a['X'] = 1;
	if (BONUS)//actually use a differen table
	{
		a[' '] = 1;
		a['+'] = 1;
		a['#'] = 1;
		a['0'] = 1;
		a['-'] = 1;
		a['.'] = 1;
	}
}

int		ft_printf(const char *format, ...)//do a char array (char **) for error handling
{
	va_list va;
	int		i;
	int		ret;
	char	table[256];//table struct it is

	va_start(va, format);
	tabler(table, &i, &ret);
	while (format[i] && format[i + 1])
	{
		if (format[i] == '%' && format[i + 1] != '%')
		{
			if (handle_bonus(format, &i, &t_flags, &t_table))
				throw();
			if (table[(unsigned char) format[i + 1]])//d, i, x, X, u
				d;
			else if (format[i + 1] == 'c')
				d;
			else if (format[i + 1] == 's' || format[i + 1] == 'p')
				d;
			else
				throw();
		}
		else
			write(1, &format[i], 1);
		i += 1 + (format[i] == '%');
	}
