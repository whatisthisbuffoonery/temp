/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 23:10:52 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/24 02:58:51 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	t_var			*buffer;
	char			*ret;
	int				start;
	int				len;

	if (refresh_buffer(&buffer, fd))
		return (NULL);
	start = buffer->count;
	while (buffer->buf[buffer->count] != '\n' && buffer->count < buffer->lim)
		buffer->count += 1;
	if (buffer->count < buffer->lim && buffer->buf[buffer->count] == '\n')
		buffer->count += 1;
	len = buffer->count - start;
	ret = malloc((len + 1) * sizeof(char));
	buffer->count = -1;
	while (++buffer->count < len)
		ret[buffer->count] = buffer->buf[start + buffer->count];
	ret[buffer->count] = '\0';
	buffer->count = start + len;
	if (get_condition(buffer, start, len))
		return (get_strjoin(ret, get_next_line(fd)));
	return (ret);
}
/*
#include <fcntl.h>

int ft_putstr(char *a)
{
	if (!a)
		return (1);
	int i = 0;
	while (a[i])
		i ++;
	write(1, a, i);
	return (0);
}

void ft_putnbr(int n)
{
	int t = 1;
	char a;
	while (n / t > 9)
		t *= 10;
	while (t)
	{
		a = ((n / t) % 10) + 48;
		write(1, &a, 1);
		t /= 10;
	}
	write(1, "\n", 1);
}

int main(int c, char **v)
{
	if (c < 4)
		return (1);
	ft_putnbr(BUFFER_SIZE);
	int fd1 = open(v[1], O_RDONLY);
	int fd2 = open(v[2], O_RDONLY);
	int fd3 = open(v[3], O_RDONLY);
	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
		return (1);
	char *a;
	int i = 0;
	while (i < 2)
	{
		a = get_next_line(fd1);
		if (ft_putstr(a))
			return (0);
		free(a);
		
		a = get_next_line(fd2);
		if (ft_putstr(a))
			return (0);
		free(a);

		a = get_next_line(fd3);
		if (ft_putstr(a))
			return (0);
		free(a);
		i ++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
//	write(1, "\n", 1);
}
*/
