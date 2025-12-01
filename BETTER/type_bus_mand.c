/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_bus_mand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:59:19 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/01 17:43:20 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_while_help(const char *format, int *index, char *type, char *flag)
{
	int	i;
	int	start;

	(void) type;
	(void) flag;
	i = *index;
	start = i;
	while (format[i] && format[i] != '%')
		i ++;
	*index = i;
	return (i == start);
}

int	type_bus(t_queue **q, const char *format)
{
	t_queue	*f;

	f = *q;
	if (!f)
		return (0);
	f->arg = format[0];
	return (2);
}
