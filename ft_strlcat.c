/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:25:08 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/19 17:47:14 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcat(char *dest, const char *src, size_t dsize)
{
	unsigned int	i;
	unsigned int	k;
	int				ret;

	i = 0;
	k = 0;
	ret = 0;
	while (src[ret])
		ret ++;
	while (dest[i] && i < dsize)
		i ++;
	if (i == dsize)
		return (i + ret);
	dsize -= i + 1;
	while (k < dsize)
	{
		dest[i + k] = src[k];
		k ++;
	}
	dest[i + k] = '\0';
	return (ret + i);
}
