/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:08:59 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/20 00:02:41 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dsize)
{
	unsigned int		i;
	unsigned int		min;
	unsigned int		ret;

	i = 0;
	min = dsize - 1;
	while (src[i])
		i ++;
	if (i < min)
		min = i;
	ret = i;
	i = 0;
	while (i < min)
	{
		dest[i] = src[i];
		i ++;
	}
	dest[i] = '\0';
	return (ret);
}
