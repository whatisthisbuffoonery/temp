/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 01:08:20 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/11 19:22:35 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		uint_help(char *ret, int flag, t_queue *q, int *i);
int		int_help(char *ret, int flag, t_queue *q, int *index);
int		prec_help(char *ret, t_queue *q, int n);
int		str_min(int size, t_queue *q);
char	*handle_flag(size_t size, t_queue *q, int *index);

char	*percent_op(t_queue *q)
{
	char	*ret;
	int		i;

	if (q && q->flags)
	{
		free(q->flags);
		q->flags = NULL;
	}
	ret = handle_flag(1 * sizeof(char), q, &i);
	if (ret)
		ret[i] = '%';
	return (ret);
}

char	*char_op(unsigned int c, t_queue *q)
{
	char	*ret;
	int		i;

	i = 0;
	ret = handle_flag(1 * sizeof(char), q, &i);
	if (!ret)
		return (NULL);
	ret[i] = c;
	if (!c)
		q->arg = '0';
	return (ret);
}

char	*uint_op(uintptr_t n, char type, t_queue *q)
{
	char			*ret;
	int				i;
	int				flag;
	unsigned int	t;
	unsigned int	base;

	t = 1;
	i = 1;
	base = 16 - (6 * (type == 'u'));
	while (n / t >= base && ++i)
		t *= base;
	flag = 2 * (type == 'p' || (q->flags && q->flags->hex));
	ret = handle_flag((i + flag) * sizeof(char), q, &i);
	if (uint_help(ret, flag, q, &i) || prec_help(ret, q, (n != 0)))
		return (ret);
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

char	*int_op(long long n, t_queue *q)
{
	char	*ret;
	int		i;
	int		t;
	int		flag;

	flag = (n < 0);
	t = 1;
	i = 1 + (flag || (q->flags && q->flags->plus_space));
	if (n < 0)
		n = 0 - n;
	while (n / t >= 10 && ++i)
		t *= 10;
	ret = handle_flag(i * sizeof(char), q, &i);
	if (int_help(ret, flag, q, &i) || prec_help(ret, q, (n != 0)))
		return (ret);
	while (t)
	{
		ret[i++] = (((n / t) % 10) + '0');
		t /= 10;
	}
	return (ret);
}

char	*ptr_op(uintptr_t src, char type, t_queue *q)
{
	int		i;
	int		k;
	int		min;
	char	*ret;
	char	*s;

	if (type == 'p')
		return (uint_op(src, type, q));
	s = (char *) src;
	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i ++;
	min = str_min(i, q);
	ret = handle_flag(min * sizeof(char), q, &i);
	if (!ret)
		return (NULL);
	k = -1;
	while (++k < min)
		ret[i + k] = s[k];
	return (ret);
}
