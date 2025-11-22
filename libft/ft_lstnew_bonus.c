/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 00:14:50 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/21 23:38:24 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
static char	*ft_strdup_help(const char *s)
{
	int		i;
	char	*ret;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i ++;
	ret = malloc((i + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ret[i] = s[i];
		i ++;
	}
	ret[i] = '\0';
	return (ret);
}
*/
t_list	*ft_lstnew(void *content)
{
	t_list	*a;

	a = malloc(sizeof(t_list));
	if (!a)
		return (NULL);
	a->next = NULL;
	a->content = content;
	return (a);
}
