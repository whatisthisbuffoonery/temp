/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:16:13 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/19 22:05:23 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*a;
	unsigned int	i;

	i = 0;
	a = (unsigned char *) s;
	while (i < n && a[i] != c)
		i ++;
	if (a[i] == c)
		return ((void *) &a[i]);
	return (NULL);
}
