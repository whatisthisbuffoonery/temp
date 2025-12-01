/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_bus_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:58:34 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/01 18:39:38 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//go handle the %p prefix functionality to extend to #x and #X
//maybe postfix 0x to 0X on the caller side

int	type_bus(t_queue **q, const char *format)
{
	t_queue	*f;
	char	*dst;
	char	type[256];
	char	flag[256];
	int		i;

	both_tables(type, flag, &f, q);
	if (!f)
		return (0);
	i = 0;
	printf_flag_help(format, &i, flag, f)
	if (!type[(unsigned char) format[i]])
		return (//err sig on arg char being \0 after call);
}
