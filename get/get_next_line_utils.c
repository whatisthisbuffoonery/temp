/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 02:10:01 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/24 03:01:58 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_strjoin(char *a, char *b, ssize_t i, ssize_t k)
{
	char	*ret;

	if (!a || !b)
		return (NULL);
	while (a[i])
		i ++;
	while (b[k])
		k ++;
	ret = malloc((i + k + 1) * sizeof(char));
	if (ret && a && b)
	{
		ret[i + k] = '\0';
		while (b && k--)
			ret[i + k] = b[k];
		while (a && i--)
			ret[i] = a[i];
	}
	free(b);
	if (!ret)
		return (a);
	free(a);
	return (ret);
}

void	refresh_buffer(t_var *file, int fd)
{
	ssize_t	i;

	i = 0;
	while ((fd != file->fd || fd < 0) && i < BUFFER_SIZE)
		file->buf[i++] = '\0';
	if (fd >= 0)
		file->lim = read(fd, file->buf, BUFFER_SIZE);
	i = 0;
	file->count = 0;
	if (fd < 0)
		file->lim = -1;
	while ((file->lim < 1) && i < BUFFER_SIZE)
		file->buf[i++] = '\0';
	file->fd = fd;
}
