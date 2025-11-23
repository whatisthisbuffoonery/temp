#include "ft_printf.h"

static void	tabler(t_tables *a, int *int1, int *int2, t_list *output)//relegate this to just d, i, x, X, u
{
	int	i;

	i = 0;
	*int1 = 0;
	*int2 = 0;
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
	a->flag[' '] = 1;
	a->flag['+'] = 1;
	a->flag['#'] = 1;
	a->flag['0'] = 1;
	a->flag['-'] = 1;
	a->flag['.'] = 1;//atoi is allowed to return '0' on invalid num
}

static void	increment(const char *format, int *index, t_list **output)
{
	int	i;

	i = *index;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '%')
			{
				i ++;
				ft_lstadd_back(output, ft_lstnew((void *) "%"));
			}
			else
				break ;
		}
		i ++;
	}
	*index = i;
}

int		ft_printf(const char *format, ...)//do a LINKED LIST AHAHAHAHAHAH for error handling
{
	va_list 	va;
	int			i;
	int			flag;
	t_list		*output;//I REALLY WANT TO add a seperate prefix string, prefix char and suffix char
	t_tables	*table;

	va_start(va, format);
	tabler(table, &i,, &flag, &output);
	while (format[i])//maybe not check format[i + 1]
	{
		if (format[i] == '%' && format[i + 1] != '%')
		{
			if (handle_flag(format, &i, &flag, table) == ERR)
				throw(format[i], output);
			if (table->type[(unsigned char) format[i]])//d, i, x, X, u
				num_help(format[i], &flag, &output, va_arg(va, int));
			else if (format[i] == 'c')
				char_help(&flag, &output, va_arg(va, char));
			else if (format[i] == 's' || format[i] == 'p')
				ptr_help(format[i], &flag, &output, va_arg(va, char *));
			i ++;
		}
		else
			increment(format, &i, &output);
	}
}
