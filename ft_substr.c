/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:07:48 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/19 22:03:32 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*ret;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i ++;
	if (start > i)
		len = 0;
	if (start + len >= i)
		len = i - start;
	ret = malloc ((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = s[i + start];
		i ++;
	}
	ret[i] = '\0';
	return (ret);
}
