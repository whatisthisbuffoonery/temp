/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:28:03 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/16 23:47:30 by dthoo            ###   ########.fr       */
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

int	print_strlen(char *a, t_queue *q)
{
	int	i;

	i = 0;
	if (!a)
		return (0);
	while (a[i])
		i ++;
	if (q->arg == '0')
	{
		i ++;
		while (a[i])
			i ++;
	}
	return (i);
}

int	process(t_queue *q, va_list *va)
{
	t_queue	*f;
	char	*new;

	f = q;
	while (f)
	{
		new = grab(f, va);
		if (!new)
			return (1);
		f->str = new;
		f = f->next;
	}
	return (0);
}
