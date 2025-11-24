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

static char	*yeet(char *a)
{
	if (a)
		free(a);
	return (NULL);
}

char	*get_strjoin(char *a, char *b)
{
	int		i;
	int		k;
	char	*ret;

	i = 0;
	k = 0;
	if (!a || !b)
		return (a);
	while (a[i])
		i ++;
	while (b[k])
		k ++;
	ret = malloc((i + k + 1) * sizeof(char));
	if (!ret)
		return (yeet(a));//this returned a, idk
	i = -1;
	k = -1;
	while (a[++i])
		ret[i] = a[i];
	while (b[++k])
		ret[i + k] = b[k];
	ret[i + k] = '\0';
	free(a);
	free(b);
	return (ret);
}

int	get_condition(t_var *buffer, int start, int len)
{
	int	a;
	int	b;

	a = (start + len >= buffer->lim);
	b = (buffer->lim == BUFFER_SIZE);
	return (a && b && buffer->buf[buffer->count - 1] != '\n');
}

int	refresh_buffer(t_var *buffer, int fd, int *me_fd)
{
	int	i;

	i = 0;
	if (fd >= 0 && *me_fd == fd && buffer->count < buffer->lim)
		return (0);
	if (fd >= 0)
		buffer->lim = read(fd, buffer->buf, BUFFER_SIZE);
	*me_fd = fd;
	buffer->count = 0;
	if (fd < 0 || buffer->lim < 1)
	{
		*me_fd = 0;
		if (buffer->lim < 0)
			write(1, " | err | ", 9);
		while (i < BUFFER_SIZE)
			buffer->buf[i++] = '\0';
		buffer->lim = 0;
		return (1);
	}
	return (0);
}
