/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 02:10:01 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/25 17:34:49 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
int	get_strjoin(char **dst, char *b, ssize_t i, ssize_t k)
{
	char	*ret;
	char	*a;

	a = *dst;
	i = 0;
	k = 0;
	while (a[i])
		i ++;
	while (b[k])
		k ++;
	ret = malloc((i + k + 1) * sizeof(char));
	if (ret)
	{
		ret[i + k] = '\0';
		while (k--)
			ret[i + k] = b[k];
		while (i--)
			ret[i] = a[i];
	}
	free(a);//OH POINTERS
	free(b);//oh pointers
	*dst = ret;
	return (!ret);
}
*/
void	refresh_buffer(t_var *file, int fd)
{
	ssize_t	i;

	i = 0;
	while ((fd != file->fd || fd < 0) && i < BUFFER_SIZE)//panic
		file->buf[i++] = '\0';
	if (fd >= 0)//on call
		file->lim = read(fd, file->buf, BUFFER_SIZE);//reads 42 or less
	i = 0;
	file->count = 0;
	if (fd < 0)
		file->lim = -1;//schizo
	while ((file->lim < 1) && i < BUFFER_SIZE)//panic again
		file->buf[i++] = '\0';
	file->fd = fd;//single fd system
}
