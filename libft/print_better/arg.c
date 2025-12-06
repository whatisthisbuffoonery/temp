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

int	uint_help(char *ret, int flag, int *i, char arg);
char	*handle_flag(size_t size, t_queue *q, int *index);
void	int_help(char *ret, int flag, t_queue *q, int *index);

char	*char_op(unsigned int c, t_queue *q)
{
//	t_list	*tmp;
//	int		*null_index;
	char	*ret;
	int		i;

	i = 0;//init here
//	null_index = malloc(sizeof(int));
	ret = handle_flag(1 * sizeof(char), q, &i);
	if (!ret)//omlllllllllll
		return (NULL);
	//*null_index = index;
	ret[i] = c;
	if (!c)//I should really insert ret here shouldnt i, make a dummy str to preserve index value
		q->arg = '0';//toss around a calculated strlen
//	else
//		free(null_index);
	return (ret);
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
	base = 16 - (6 * (type == 'u'));//still accurate in bonus
	while (n / t >= base && ++i)
		t *= base;
	flag = 2 * (type == 'p' || (q->flags && q->flags->hex));//actually malloc count is ok
	ret = handle_flag((i + flag) * sizeof(char), q, &i); //2 * type == p was here// 3 lines too smol, suppose repurposing uint helper to take #X
																//does not write 0x prefix
	if (uint_help(ret, flag, &i, q->arg))//capital X
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

	flag = (n < 0);
	t = 1;
	i = 1 + (flag || (q->flags && q->flags->plus_space));//changed to ||
	if (n < 0)
		n = 0 - n;
	while (n / t >= 10 && ++i)
		t *= 10;
	ret = handle_flag(i * sizeof(char), q, &i);//handles i = flag
	if (!ret)
		return (NULL);
	//if (flag)
	//	ret[i++] = '-';//int helper here
	int_help(ret, flag, q, &i);
	while (t)
	{
		ret[i++] = (((n / t) % 10) + '0');
		t /= 10;
	}
	return (ret);
}

char	*ptr_op(uintptr_t src, char type, t_queue *q)
{
	int		i;
	char	*ret;
	char	*s;

	if (type == 'p')
		return (uint_op(src, type, q));
	s = (char *) src;
	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i ++;
	ret = handle_flag(i * sizeof(char), q, &i);
	if (!ret)
		return (NULL);
	i --;//was i = -1 before
	while (s[++i])
		ret[i] = s[i];
	return (ret);
}
