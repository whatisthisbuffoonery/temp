/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flag_mand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 21:19:03 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/03 03:26:51 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_mand.h"

char	*handle_flag(size_t size, t_queue *q, int *index)
{
	char	*ret;

	(void) q;
	ret = malloc(size + 1);
	if (!ret)
		return (NULL);
	ret[size] = '\0';
	*index = 0;//pretend there was prefix work here
	return (ret);
}

int	valid_cond_printf(const char *format, char *type, char *flag, int *i)
{
	(void) flag;
	return (format[*i] != '%' && !type[(unsigned char) format[*i]]);
}
