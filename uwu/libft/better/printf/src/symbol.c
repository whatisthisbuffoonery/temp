#include "ft_printf.h"

int	str_op(int *len, t_write_head w, char *str);
int	hex_op(char c, int *len, t_write_head w);
int	char_op(char src, int *len, t_write_head w);
int	int_op(int *len, t_write_head w);
int	uint_op(int *len, t_write_head w);

static void	fill_numeric(t_pf_specifiers *sp, const char **format)
{
	int	i;

	if (sp->plus)
		sp->space = 0;
	if (sp->dash)
		sp->zero = 0;
	if (!ft_isdigit(**format) && **format != '.')
		return ;
	i = 0;
	if (**format != '.')
	{
		sp->width = ft_atoi_ind(&(*format)[i], &i);
		sp->w_set = 1;
	}
	if ((*format)[i] == '.')
	{
		i ++;
		sp->precision = ft_atoi_ind(&(*format)[i], &i);
		sp->p_set = 1;
		sp->zero = 0;//allowed to assume precision was for int/uint //maybe catch error instead?
	}
	*format = &(*format)[i];
}

static void	fill_specifiers(t_pf_specifiers *sp, const char **format)
{
	int	i;

	i = 1;//landed on % sign
	while ((*format)[i])
	{
		if ((*format)[i] == '0')
			sp->zero = 1;
		else if ((*format)[i] == '-')
			sp->dash = 1;
		else if ((*format)[i] == '#')
			sp->hex = 1;
		else if ((*format)[i] == ' ')
			sp->space = 1;
		else if ((*format)[i] == '+')
			sp->plus = 1;
		else
			break ;
		i ++;
	}
	*format = &(*format)[i];
}

//TODO length modifier, stuff another function after numeric
//%[$][flags][width][.precision][length modifier][conversion]
//TODO n is an outparam for number of bytes written thus far
int	printf_symbol(const char **format, int *len, t_write_head w)
{
	int				i;
	char			c;

	ft_memset(&w.sp, 0, sizeof(t_pf_specifiers));
	fill_specifiers(&w.sp, format);
	fill_numeric(&w.sp, format);
	c = **format;
	if (c)
		*format = &(*format)[1];
	if (c == 'c' || c == '%')
		return (char_op(c, len, w));
	else if (c == 's')
		return (str_op(len, w, (char *) va_arg(*w.va, uintptr_t)));
	ft_memset(w.buf, 0, sizeof(char) * NUM_BUFFER);
	if (c == 'd' || c == 'i')
		return (int_op(len, w));
	else if (c == 'x' || c == 'X' || c == 'p')// %p == %#x lowercase
		return (hex_op(c, len, w));
	else if (c == 'u')
		return (uint_op(len, w));
	i = printf_write(w, "[printf error]", 14);//write an error and keep going
	*len += i;
	return (i < 0);
}

//0 precision suppresses all numbers when they are 0
//floats get 0 decimal places instead
