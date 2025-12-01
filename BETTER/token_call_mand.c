/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_call_mand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:57:42 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/01 13:08:00 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	type_bus(t_queue **q, const char *format);

static void	*tantrum(t_queue **a, char **b)
{
	if (*a)
	{
		free(*a);
		*a = NULL;
	}
	if (b && *b)
	{
		free(*b);
		*b = NULL;
	}
	return (NULL);
}

t_queue	*new_op(const char *format, int *index)
{
	t_queue	*ret;

	ret = q_new();
	*index += type_bus(&ret, &format[1]);
	if (!ret)
		return (tantrum(&ret, 0));
	ret->type = op;
	return (ret);
}

t_queue	*new_str(const char *format, int start, int *end)
{
	int		i;
	int		flag;
	t_queue	*ret;
	char	*res;

	ret = q_new();
	flag = (format[*end] && format[*end + 1] == '%');
	*end += flag;
	res = malloc(((*end - start) + 1) * sizeof(char));
	i = -1;
	if (!ret || !res)
		return (tantrum(&ret, &res));
	while (start + ++i < *end)
		res[i] = format[i + start];
	res[i] = '\0';
	ret->str = res;
	*end += flag;
	ret->type = str;
	return (ret);
}
