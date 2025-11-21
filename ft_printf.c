#include "ft_printf.h"

static void	tabler(t_tables *a, int *int1, t_list *output)//relegate this to just d, i, x, X, u
{
	int	i;

	i = 0;
	*int1 = 0;
	*output = 0;
	a = malloc(sizeof(t_tables));
	while (i < 256)
	{
		a->type[i] = 0;
		a->flag[i++] = 0;
	}
	a->type['d'] = 1;
	a->type['i'] = 1;
	a->type['u'] = 1;
	a->type['x'] = 1;
	a->type['X'] = 1;
	a->dot = BONUS;//atoi is allowed to return '0' on invalid num
	if (BONUS)//actually use a differen table
	{
		a->flag[' '] = 1;
		a->flag['+'] = 1;
		a->flag['#'] = 1;
		a->flag['0'] = 1;
		a->flag['-'] = 1;
	}
}

int		handle_flag(const char *format, int *i, t_tables *table)
{
	*i += 1;
	if (!format[*i])
		return (1);
	if (table->flag[(unsigned char) format[*i]])
		BONUS(format, i, );
	return (0);
}

int		ft_printf(const char *format, ...)//do a LINKED LIST AHAHAHAHAHAH for error handling
{
	va_list 	va;
	int			i;
	t_list		*output;
	t_tables	*table;

	va_start(va, format);
	tabler(table, &i, output);
	while (format[i])//maybe not check format[i + 1]
	{
		if (format[i] == '%' && format[i + 1] != '%')
		{
			if (handle_flag(format, &i, table))
				throw(format[i], output);
			if (table->type[(unsigned char) format[i]])//d, i, x, X, u
				num_help(format, &i, output, va_arg(va, int));
			else if (format[i] == 'c')
				char_help(format, &i, output, va_arg(va, char));
			else if (format[i] == 's' || format[i] == 'p')
				ptr_help(format, &i, output, va_arg(va, char *);
			else
				throw(format[i], output);
		}
		else
			increment(format, &i, &output);
	}
