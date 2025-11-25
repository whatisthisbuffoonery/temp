/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand_print_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 22:58:59 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/26 00:35:49 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*package_help(char *ret, char type, int i, int flag)
{
	if (!ret)
		return (NULL);
	if (type == 'p')
	{
		ret[0] = '0';
		ret[1] = 'x';
	}
	if (type == 'd' || type == 'i')
	{
		if (flag)
			ret[0] = '-';
	}
	ret[i] = '\0';
	return (ret);
}

char	*print_base_unsigned(uintptr_t n, int base, char type)
{
	int		t;
	int		i;
	char	hex;
	char	*ret;

	t = 1;
	i = 1;
	hex = 32 * (type == 'X');
	while (n / t > base - 1 && ++i)
		t *= base;
	ret = malloc((i + 1 + (2 * (type == 'p'))) * sizeof(char));
	i = 2 * (type == 'p');
	while (ret && t)
	{
		ret[i] = ((n / t) % base) + '0';
		if (ret[i++] > '9')
			ret[i - 1] += ('a' - '0') - hex;
		t /= base;
	}
	return (package_help(ret, type, i, 0));
}

char	*print_base_signed(intptr_t n, char type)
{
	int		i;
	int		t;
	int		num;
	int		flag;
	char	*ret;

	if (type == 'x' || type == 'X' || type == 'u')
		return (print_base_unsigned(n, 16 - (6 * (type == 'u')), type));
	t = 1;
	flag = (n < 0);
	i = flag + 1;
	if (flag)
		n = 0 - n;
	while (n / t > 9 && ++i)
		t *= 10;
	ret = malloc((i + 1) * sizeof(char));
	i = flag;
	while (ret && t)
	{
		ret[i++] = ((n / t) % 10) + '0';
		t /= 10;
	}
	return (package_help(ret, type, i, flag));
}

char	print_ptr(char type, char *src)
{
	int		i;
	char	*ret;

	i = 1;
	if (type == 's')
	{
		i = -1;
		ret = malloc(ft_strlen(src) + 1 * sizeof(char));
		if (!ret)
			return (NULL);
		while (src[++i])
			ret[i] = src[i];
	}
	else
		ret = print_base_unsigned((uintptr_t) src, 16, type);
	return (ret);
}

static void	tabler(char *table, int *i, char **ret)
{
	*i = 0;
	*ret = NULL;
	ft_memset(table, 0, 256);
	table['d'] = 1;
	table['i'] = 1;
	table['u'] = 1;
	table['x'] = 1;
	table['X'] = 1;
}
