/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flag_mand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 21:19:03 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/01 21:38:29 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.c"

char	*handle_flag(size_t size, t_queue *q, int *index, int negative)
{
	int		hex_prefix;
	char	*ret;

	hex_prefix = 2 * (q->arg == 'p');
	ret = malloc((size + hex_prefix + negative) * sizeof(char));
	if (!ret)
		return (NULL);
	if (hex_prefix)
	{
		ret[0] = '0';
		ret[1] = 'x';
	}
	else if (negative)
		ret[0] = '-';
	if (hex && negative)
		write(1, "dude your flags are fucked\n", 25);
	*index = hex_prefix + negative;
}
