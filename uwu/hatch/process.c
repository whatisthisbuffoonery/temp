/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:28:03 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/11 19:23:14 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*grab(t_queue *q, va_list *va)
{
	char	cmp;

	if (q->type == str)
		return (q->str);
	else if (q->type == op)
	{
		cmp = q->arg;
		if (cmp == '%')
			return (percent_op(q));
		if (cmp == 'c')
			return (char_op(va_arg(*va, int), q));
		else if (cmp == 's' || cmp == 'p')
			return (ptr_op(va_arg(*va, uintptr_t), cmp, q));
		else if (cmp == 'd' || cmp == 'i')
			return (int_op(va_arg(*va, int), q));
		else if (cmp == 'u' || cmp == 'x' || cmp == 'X')
			return (uint_op(va_arg(*va, unsigned int), cmp, q));
	}
	return (NULL);
}

static int	print_strlen(char *a, t_queue *q)
{
	int	i;

	i = 0;
	if (!a)
		return (0);
	while (a[i])
		i ++;
	if (q->arg == '0')
	{
		q->arg = 'c';
		i ++;
		while (a[i])
			i ++;
	}
	return (i);
}

static char	*print_strjoin(char *dst, char *src, t_queue *f, int *len)
{
	char	*ret;
	int		i;
	int		k;
	int		src_len;

	if (!dst || !src)
		return (NULL);
	src_len = print_strlen(src, f);
	ret = malloc((*len + src_len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = -1;
	k = -1;
	while (++i < *len)
		ret[i] = dst[i];
	while (++k < src_len)
		ret[i + k] = src[k];
	ret[i + k] = '\0';
	if (f->type == op)
		free(src);
	*len += src_len;
	return (ret);
}

static void	*tantrum_boogaloo(char *new, char *tmp, t_queue *f)
{
	if (new && f->type == op)
		free(new);
	if (tmp)
		free(tmp);
	return (NULL);
}

char	*process(t_queue *q, va_list *va, int *len)
{
	t_queue	*f;
	char	*ret;
	char	*tmp;
	char	*new;

	f = q->next;
	ret = grab(q, va);
	if (!ret)
	{
		return (NULL);
	}
	*len = print_strlen(ret, q);
	while (f)
	{
		new = grab(f, va);
		tmp = print_strjoin(ret, new, f, len);
		if (ret != q->str)
			free(ret);
		if (!tmp || !new)
			return (tantrum_boogaloo(new, tmp, f));
		f = f->next;
		ret = tmp;
	}
	return (ret);
}
