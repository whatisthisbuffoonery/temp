/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flag_mand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 21:19:03 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/03 02:01:00 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_mand.h"

char	*handle_flag(size_t size, t_queue *q, int *index)
{
	char	*ret;

	(void) q;
	ret = malloc(size);
	if (!ret)
		return (NULL);
	ret[size - 1] = '\0';
	*index = 0;//pretend there was prefix work here
	return (ret);
}
