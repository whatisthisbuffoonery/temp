/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:07:48 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/21 22:49:57 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	var_help(int *s, unsigned int start, size_t len, int *l)
{
	*l = len;
	*s = start;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	int		ft_len;
	int		ft_start;
	char	*ret;

	if (!s)
		return (NULL);
	while (s[i])
		i ++;
	var_help(&ft_start, start, len, &ft_len);
	if (ft_start > i)
		ft_len = 0;
	else if (ft_start + ft_len > i)
		ft_len = i - ft_start;
	ret = malloc ((ft_len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < ft_len)
	{
		ret[i] = s[i + start];
		i ++;
	}
	ret[i] = '\0';
	return (ret);
}
