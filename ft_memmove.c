/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 22:09:35 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/17 22:27:54 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memmove(void *dest, void *src, unsigned int n)
{
	unsigned int		i;
	int					move;
	char				*d;
	char				*s;

	i = 0;
	d = (char *) dest;
	s = (char *) src;
	move = 1;
	if (d > s)
	{
		move = -1;
		i = n - 1;
		n = 0;
	}
	while (i != n)
	{
		d[i] = s[i];
		i += move;
	}
	return (dest);
}
