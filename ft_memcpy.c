/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 21:54:26 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/17 22:08:43 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memcpy(void *dest, void *src, int n)
{
	int		i;
	char	*d;
	char	*s;

	i = 0;
	d = (char *) dest;
	s = (char *) src;
	while (i < n)
	{
		d[i] = s[i];
		i ++;
	}
	return (dest);
}
