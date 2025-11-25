/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:19:12 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/26 00:35:39 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_join(char **dst, char *src, int *complain)
{
	char	*ret;

	ret = NULL;
	if (!*dst)
	{
		*dst = src;
		return ;
	}
	if (src)
	{
		ret = ft_strjoin(*dst, src);
		free(src);
	}
	free(*dst);
	if (!ret)
		*complain = -1;
	*dst = ret;
}

static int	append(const char *format, char **dst, int *index, int *end)
{
	char	*ret;
	int		flag;
	int		i;
	int		start;
	int		stop;

	i = -1;
	flag = 0;
	start = *index;
	if (format[*end] && format[*end + 1] == '%')
		flag = 1;
	*end += flag;
	stop = *end;
	ret = malloc(((stop - start) + 1) * sizeof(char));
	if (!ret)
	{
		if (*dst)
			free(*dst);
		*dst = NULL;
		return ((*start = -1), -1);
	}
	while (start + ++i < stop)
		ret[i] = format[i + start];
	ret[i] = '\0';
	*index = stop + 1;
	print_join(dst, ret, &i);
	return (!format[stop] || !flag || i < 0);
}

static void	increment(const char *format, char **ret, int *index, int size)
{
	int	i;

	i = *index;
	while (i < size && *index >= 0)
	{
		while (i < size && format[i] != '%')
			i ++;
		if (append(format, ret, index, &i))
			break ;
	}
}

static int	handle_arg(const char *format, char **dst, va_list va, char *table)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (format[i])
	{
		if (table[(unsigned char) format[i]])
			ret = print_base_signed(format[i], va_arg(va, int));
		else if (format[i] == 's' || format[i] == 'p')
			ret = print_ptr(format[i], va_arg(va, char *));
		else if (format[i] == 'c')
		{
			ret = malloc(2 * sizeof(char));
			if (ret)
			{
				ret[0] = va_arg(va, char);
				ret[1] = '\0';
			}
		}
		print_join(dst, ret, &i);
		if (i < 0)
			table[0] = 1;
	}
	return (1);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		size;
	char	*ret;
	char	table[256];
	va_list	va;

	if (!format || !*format)
		return (NULL);
	tabler(table, &i, &ret);
	va_start(va, format);
	size = ft_strlen(format);
	while (i >= 0 && size > 0 && i < size && !table[0])
	{
		increment(format, &ret, &i, size);
		if (!ret || (format[i - 1] == '%' && !format[i]))
		{
			if (ret)
				free(ret);
			ret = NULL;
			break ;
		}
			i += handle_arg(&format[i], &ret, va, table);
	}
	va_end(va);
	if (ret)
		write(1, ret, ft_strlen(ret));
	return (!ret);
}
