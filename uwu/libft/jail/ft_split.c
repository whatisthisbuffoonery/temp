/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:12:57 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/20 00:00:54 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_substr_help(char const *s, unsigned int start, size_t len)
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
	i = 0;
	if (!ret)
		return (0);
	while (i < len)
	{
		ret[i] = s[i + start];
		i ++;
	}
	ret[i] = '\0';
	return (ret);
}

static int	while_help(char const *s, char c, int *index, int *zero)
{
	int	i;

	i = *index;
	if (!s || !s[0])
		return (0);
	if (*zero)
	{
		i ++;
		*zero = 0;
	}
	while (s[i] && s[i + 1])
	{
		if ((s[i] == c && s[i + 1] && s[i + 1] != c) || (!i && s[i] != c))
		{
			*zero = !i;
			i += (s[i] == c);
			*index = i;
			return (1);
		}
		i ++;
	}
	return (0);
}

static void	var_help(int *a, int *b, int *c, char ***d)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = NULL;
}

static int	err_help(char **ret, char ***err, int *count, int loop)
{
	if (!ret)
		return (1);
	if (!*count && !loop)
	{
		ret[0] = 0;
		*err = ret;
		return (1);
	}
	if (loop && !ret[*count])
	{
		while (*count > 0)
		{
			*count -= 1;
			free(ret[*count]);
		}
		free(ret);
		return (1);
	}
	*count += 1;
	return (!ret);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		k;
	int		count;
	char	**err;
	char	**ret;

	var_help(&i, &count, &k, &err);
	while (while_help(s, c, &i, &k))
		count ++;
	ret = malloc((count + 1) * sizeof(char *));
	if (err_help(ret, &err, &count, 0))
		return (err);
	var_help(&i, &count, &k, &err);
	while (while_help(s, c, &i, &k))
	{
		k = i + 1;
		while (s[k] && s[k] != c)
			k ++;
		ret[count] = ft_substr_help(s, i, k - i);
		if (err_help(ret, &err, &count, 1))
			return (NULL);
	}
	ret[count] = NULL;
	return (ret);
}
