#include "ft_printf.h"

int	handle_flag(const char *format, int *i, int *flag, t_tables *table)
{
	unsigned char	c;

	*i += 1;
	*flag = 0;
	c = (unsigned char) format[*i];
	if (table->type[c] || c == 'c' || c == 's' || c == 'p' || c == '%')
		return (0);
	return (ERR);
}
