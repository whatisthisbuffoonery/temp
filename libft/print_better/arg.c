/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 01:08:20 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/03 06:49:47 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_mand.h"

//all these take an arg node now, AND they call handle_flag for the malloc


char	*handle_flag(size_t size, t_queue *q, int *index);

char	*char_op(unsigned int c, t_queue *q, t_list **null, int index)
{
	int		*null_index;
	char	*ret;
	int		i;

	(void) q;
	i = 0;//init here
	null_index = malloc(sizeof(int));
	ret = handle_flag(2 * sizeof(char), q, &i);
	if (!ret || !null_index)//omlllllllllll
		return (NULL);
	*null_index = index;
	ret[i] = c;
	if (!c)//to insert arg node here
		ft_lstadd_back(null, ft_lstnew(null_index, NULL));
	else
		free(null_index);
	return (ret);
}

static int	uint_help(char *ret, int flag, int *i)
{
	if (!ret)
		return (1);
	if (flag)
	{
		ret[*i] = '0';
		ret[*i + 1] = 'x';
	}
	*i += flag;//handle_flag placed it after flag requirements, used to be i = flag
	return (0);
}

char	*uint_op(uintptr_t n, char type, t_queue *q)
{
	char			*ret;
	int				i;
	int				flag;
	unsigned int	t;
	unsigned int	base;

	t = 1;
	i = 1;
	(void) q;
	base = 16 - (6 * (type == 'u'));//still accurate in bonus
	while (n / t >= base && ++i)
		t *= base;
	flag = 2 * (type == 'p' || (q->flags && q->flags->hex));//plzz unset hex if type not x or X
	ret = handle_flag((i + 1 + flag) * sizeof(char), q, &i); //2 * type == p was here// 3 lines too smol, suppose repurposing uint helper to take #X
																//does not write 0x prefix
	if (uint_help(ret, flag, &i))
		return (NULL);
	while (t)
	{
		ret[i] = "0123456789abcdef"[((n / t) % base)];
		if (type == 'X' && ret[i] > '9')
			ret[i] -= 32;
		i ++;
		t /= base;
	}
	return (ret);
}

char	*int_op(long long n, t_queue *q)//propose checking hex flag in caller
{
	char	*ret;
	int		i;
	int		t;
	int		flag;

	(void) q;
	flag = (n < 0 && q->flags && !q->flags->plus_space);
	t = 1;
	i = 1 + flag;
	if (n < 0)
		n = 0 - n;
	while (n / t >= 10 && ++i)
		t *= 10;
	ret = handle_flag((i + 1) * sizeof(char), q, &i);//handles i = flag
	if (!ret)
		return (NULL);
	if (flag)
		ret[i++] = '-';
	while (t)
	{
		ret[i++] = (((n / t) % 10) + '0');
		t /= 10;
	}
	//ret[i] = '\0';// handle_flag will terminate
	return (ret);
}

char	*ptr_op(char *s, char type, t_queue *q)
{
	int		i;
	char	*ret;

	if (!s)
		return (NULL);
	if (type == 'p')
		return (uint_op((uintptr_t) s, type, q));
	(void) q;
	i = 0;
	while (s[i])
		i ++;
	ret = handle_flag((i + 1) * sizeof(char), q, &i);
	if (!ret)
		return (NULL);
	i --;//was i = -1 before
	while (s[++i])
		ret[i] = s[i];
	return (ret);
}
