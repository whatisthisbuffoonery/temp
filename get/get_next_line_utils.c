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

char	*get_strjoin(char *a, char *b)
{
	int		i;
	int		k;
	char	*ret;

	i = 0;
	k = 0;
	if (!a)
		return (NULL);
	if (!b)
		return (a);
	while (a[i])
		i ++;
	while (b[k])
		k ++;
	ret = malloc((i + k + 1) * sizeof(char));
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
	int	c;

	a = (start + len >= buffer->lim);
	b = (buffer->buf[buffer->count] != '\n');
	c = (buffer->lim == BUFFER_SIZE);
	return (a && b && c);
}

int	refresh_buffer(t_var *buffer, int fd)
{
	if (fd < 0)
		return (1);
	if (buffer->count != buffer->lim)
		return (0);
	buffer->lim = read(fd, buffer->buf, BUFFER_SIZE);
	buffer->count = 0;
	if (!buffer->lim)
		return (1);
	return (0);
}
