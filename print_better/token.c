#include "ft_printf.h"

//make a bonus tabler, this file is the only one using 'flag'
//new_op passes 'type' to type bus, checking done beforehand vvv
//i think ill merge the bonus features into type bus mand
//rework valid vvv
//printf doesnt write null chars, keep the !size check// excluding %c args, thats fixed
//this is also the only file using while help, that only uses 'flag'
//just put it here wth
//phenomenon: input drought. bring pencil and paper next time pls
// have count_flag for validation and then handle_flag (not using 'flag') for the arg malloc replacement
//PROPOSE leaving hex # out of 'flag' to check ordering 

void	tabler(char *type, char *flag, int *a, int *b);
t_queue	*new_op(const char *format, int *index, char *type);
t_queue	*new_str(const char *format, int start, int *end);
int valid_cond_printf(const char *format, char *type, char *flag, int *i);

static int valid(const char *format, int size, char *type, char *flag)
{
	int	i;

	i = 0;
	if (!format || !format[0] || size <= 0)
		return (1);
	if (size == 1 && format[0] == '%')
		return (1);
	if (size > 1 && format[size - 2] != '%' && format[size - 1] == '%')
		return (1);
	while (i + 1 < size)//having # out and not using a func is not feasible for line count
	{
		if (format[i] == '%')
		{
			i ++;
			if (valid_cond_printf(format, type, flag, &i))
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
	char	type[256];//we are respawning this table afterwards. The alternative is spawning it in main and having 4 params here. fuuuuuuuuu
	char	flag[256];
	t_queue	*tmp;

	tabler(type, flag, &i, &start);
	if (valid(format, size, type, flag))
	{
		write(1, "Invalid format string detected\n", 31);
		return ;
	}
	while (i < size)
	{
		while (i < size && format[i] != '%')
			i ++;
		if (format[start] == '%' && format[start + 1] != '%')
			tmp = new_op(&format[i], &i, type);//tmp null, dont need table
		else if (format[start])
			tmp = new_str(format, start, &i);//tmp null
		if (enq(q, tmp))
			return ;//signals q null, tmp->next = null
		start = i;//both funcs edit i to be either a % or outside an arg// explicit bomb out on no match
	}
}
