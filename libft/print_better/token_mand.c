#include "header_mand.h"

void	tabler(char *table, int *a, int *b);
t_queue	*new_op(const char *format, int *index, char *table);
t_queue	*new_str(const char *format, int start, int *end);

static int valid(const char *format, int size, char *table, int i)
{
	if (!format || !format[0] || size <= 0)
		return (1);
	if (size == 1 && format[0] == '%')
		return (1);
	if (format[size - 2] != '%' && format[size - 1] == '%')
		return (1);
	while (i + 1 < size)
	{
		if (format[i] == '%')
		{
			i ++;
			if (format[i] != '%' && !table[(unsigned char) format[i]])
				return (1);
		}
		i ++;
	}
	return (0);
}

void	printf_tokens(const char *format, t_queue **q, int size)
{
	int		i;
	int		start;
	char	table[256];
	t_queue	*tmp;

	tabler(table, &i, &start);
	if (valid(format, size, table, 0))
	{
		write(1, "Invalid format string detected\n", 31);
		return ;
	}
	while (i < size)
	{
		while (i < size && format[i] != '%')
			i ++;
		if (format[start] == '%' && format[start + 1] != '%')
			tmp = new_op(&format[i], &i, table);//tmp null, dont need table
		else if (format[start])
			tmp = new_str(format, start, &i);//tmp null
		if (enq(q, tmp))
			return ;//signals q null, tmp->next = null
		start = i;//both funcs edit i to be either a % or outside an arg// explicit bomb out on no match
	}
}
