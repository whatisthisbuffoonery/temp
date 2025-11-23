/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 02:10:01 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/24 02:49:15 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

int	refresh_help(t_var *buffer, int fd)
{
	if (buffer->count != buffer->lim)
		return (0);
	buffer->lim = read(fd, buffer->buf, BUFFER_SIZE);
	buffer->count = 0;
	if (!buffer->lim)
		return (1);
	return (0);
}

static t_var	*new_node(int fd)
{
	t_var	*a;

	a = malloc(sizeof(t_var));
	a->fd = fd;
	a->count = 0;
	a->lim = 0;
	a->next = NULL;
	return (a);
}

int	refresh_buffer(t_var **buffer, int fd)
{
	static t_var	*head;
	t_var			*curr;

	if (!head)
		head = new_node(fd);
	curr = head;
	while (curr->next && curr->fd != fd)
		curr = curr->next;
	if (curr->fd != fd)
	{
		curr->next = new_node(fd);
		curr = curr->next;
	}
	*buffer = curr;
	return (refresh_help(curr, fd));
}
