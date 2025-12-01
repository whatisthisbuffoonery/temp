/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_func_mand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:50:09 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/01 19:35:43 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	clear_q(t_queue **q, char *ret)
{
	t_queue	*f;
	t_queue	*tmp;

	f = NULL;
	if (q && *q)
		f = *q;
	while (f)
	{
		tmp = f->next;
		if (f->str && f->str != ret)
			free(f->str);
		free(f);
		f = tmp;
	}
	if (q)
		*q = NULL;
}

t_queue	*q_new(void)
{
	t_queue	*tmp;

	tmp = malloc(sizeof(t_queue));
	if (!tmp)
		return (NULL);
	tmp->next = NULL;
	tmp->str = NULL;
	tmp->arg = '\0';
	tmp->flags = NULL;
	tmp->type = nil;
	return (tmp);
}

static int	nono(t_queue *new)
{
	write(1, "nono? WHAT DO YOU MEAN NONO\n", 28);
	if (new)
		free(new);
	return (1);
}

int	enq(t_queue **q, t_queue *new)
{
	t_queue	*f;

	if (!q)
		return (nono(new));
	if (!new)
	{
		clear_q(q, 0);
		return (1);
	}
	if (!*q)
	{
		*q = new;
		return (0);
	}
	f = *q;
	while (f->next)
		f = f->next;
	f->next = new;
	return (0);
}
