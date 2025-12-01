/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_mand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:47:56 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/01 20:04:55 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*grab(t_queue *q, va_list va)
{
	char	cmp;

	if (q->type == str)
		return (q->str);
	else if (q->type == op)
	{
		cmp = q->arg;
		if (cmp == 'c')
			return (char_op(va_arg(va, unsigned int), q));
		else if (cmp == 's' || cmp == 'p')
			return (ptr_op(va_arg(va, char *), cmp, q));
		else if (cmp == 'd' || cmp == 'i')
			return (int_op(va_arg(va, int), q));
		else if (cmp == 'u' || cmp == 'x' || cmp == 'X')
			return (uint_op(va_arg(va, unsigned int), cmp, q));
		write(1, &cmp, 1);
		write(1, "	<--  who put this here\n", 25);
	}
	else
		write(1, "nil type in queue???\n", 22);
	return (NULL);
}

static char	*print_strjoin(char *dst, char *src, t_queue *f)
{
	char	*ret;
	int		i;
	int		k;

	if (!dst || !src)
		return (NULL);
	ret = malloc((ft_strlen(dst) + ft_strlen(src) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = -1;
	k = -1;
	while (dst[++i])
		ret[i] = dst[i];
	while (src[++k])
		ret[i + k] = src[k];
	ret[i + k] = '\0';
	if (f->type == op)
		free(src);
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

char	*process(t_queue *q, va_list va)
{
	t_queue	*f;
	char	*ret;
	char	*tmp;
	char	*new;

	f = q->next;
	ret = grab(q, va);
	if (!ret)
		return (NULL);
	while (f)
	{
		new = grab(f, va);
		tmp = print_strjoin(ret, new, f);
		if (ret != q->str)
			free(ret);
		if (!tmp || !new)
			return (tantrum_boogaloo(new, tmp, f));
		f = f->next;
		ret = tmp;
	}
	return (ret);
}
