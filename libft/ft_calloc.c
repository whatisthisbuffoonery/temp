/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:09:35 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/19 23:56:37 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned long	intmax;
	unsigned int	i;
	char			*ret;

	if (!nmemb || !size)
	{
		ret = malloc(0);
		return (ret);
	}
	i = 0;
	intmax = 1;
	while (i++ < 32)
		intmax *= 2;
	intmax --;
	i = intmax / size;
	if (nmemb > i)
		return (0);
	size *= nmemb;
	ret = malloc(size);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < size)
		ret[i++] = '\0';
	return ((void *) ret);
}
