/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_mand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:58:53 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/01 21:28:31 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_flag(size_t size, t_queue *q, int *index, int negative);

char	*char_op(unsigned int c, t_queue *q)
{
	char	*ret;
	int		i;

	ret = handle_flag(2 * sizeof(char), q, &i, 0);
	if (!ret)
		return (NULL);
	ret[i] = c;
	ret[i + 1] = '\0';
	return (ret);
}
/*
static int	uint_help(char *ret, int flag, int *i)
{
	if (!ret)
		return (1);
	if (flag)
	{
		ret[0] = '0';
		ret[1] = 'x';
	}
	ret[*i + flag] = '\0';
	*i = flag;
	return (0);
}
*/
// + (2 * (type == 'p')) was here in the malloc

char	*uint_op(uintptr_t n, char type, t_queue *q)
{
	char			*ret;
	int				i;
	unsigned int	t;
	unsigned int	base;

	t = 1;
	i = 1;
	base = 16 - (6 * (type == 'u'));
	while (n / t >= base && ++i)
		t *= base;
	ret = handle_flag(i + 1 * sizeof(char), q, &i, 0);
	if (!ret)
		return (NULL);
	while (t)
	{
		ret[i] = "0123456789abcdef"[((n / t) % base)];
		if (type == 'X' && ret[i] > '9')
			ret[i] -= 32;
		i ++;
		t /= base;
	}
	return (ret);
}

static void	ft_printf_line_shave(int *i, long long *n, int *t, int *flag)
{
	*t = 1;
	*flag = (*n < 0);
	*i = 1 + *flag;
	if (*flag)
		*n = 0 - *n;
}

char	*int_op(long long n, t_queue *q)
{
	char	*ret;
	int		i;
	int		t;
	int		flag;

	ft_printf_line_shave(&i, &n, &t, &flag);
	while (n / t >= 10 && ++i)
		t *= 10;
	ret = handle_flag((i + 1) * sizeof(char), q, &i, flag);
	if (!ret)
		return (NULL);
	if (flag)
		ret[0] = '-';
	ret[i] = '\0';
	while (t)
	{
		ret[i++] = (((n / t) % 10) + '0');
		t /= 10;
	}
	return (ret);
}

char	*ptr_op(char *s, char type, t_queue *q)
{
	int		i;
	char	*ret;

	if (!s)
		return (NULL);
	if (type == 'p')
		return (uint_op((uintptr_t) s, type));
	i = 0;
	while (s[i])
		i ++;
	ret = handle_flag((i + 1) * sizeof(char), q, &i, 0);
	if (!ret)
		return (NULL);
	i = -1;
	while (s[++i])
		ret[i] = s[i];
	ret[i] = '\0';
	return (ret);
}
