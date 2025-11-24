/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 23:10:52 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/24 03:04:23 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_var	buffer;
	static int		me_fd;
	char			*ret;
	int				start;
	int				len;

	if (refresh_buffer(&buffer, fd, &me_fd))
		return (NULL);
	start = buffer.count;
	while (buffer.count < buffer.lim && buffer.buf[buffer.count] != '\n')
		buffer.count += 1;
	if (buffer.count < buffer.lim && buffer.buf[buffer.count] == '\n')
		buffer.count += 1;
	len = buffer.count - start;
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	buffer.count = -1;
	while (++buffer.count < len)
		ret[buffer.count] = buffer.buf[start + buffer.count];
	ret[buffer.count] = '\0';
	buffer.count = start + len;
	if (fd >= 0 && me_fd == fd && get_condition(&buffer, start, len))
		return (get_strjoin(ret, get_next_line(fd)));
	return (ret);
}
/*
#include <fcntl.h>

void ft_putstr(char *a)
{
	int i = 0;
	if (!a)
	{
		ft_putstr("(null)\n");
		return ;
	}
	while (a[i])
		i ++;
	write(1, a, i);
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

int ft_strlen(char *a)
{
	int i = 0;
	while (a && a[i])
		i ++;
	return (i);
}

void read_file(int fd, size_t lines)
{
	char *a;
	if (!lines)
		lines = -1;
	while (lines--)
	{
		a = get_next_line(fd);
		if (a && a[0] == '\n')
			ft_putstr("nl\n");
		if (a && a[0] == '\0')
			ft_putstr(".\n");
		ft_putstr(a);
		//ft_putnbr(ft_strlen(a));
		if (!a)
			return ;
		free(a);
	}
}

int main(int c, char **v)
{
	if (c < 2)
		return (1);
	ft_putnbr(BUFFER_SIZE);
	(void) v;
	int fd = open(v[1], O_RDONLY);
	if (fd < 0)
		return (1);
	read_file(fd, 2);
	close(fd);
//	fd = open("not_a_file.txt", O_WRONLY);
//	fd = -100;
//	read_file(fd, 0);
	fd = open(v[1], O_RDONLY);
	if (fd < 0)
		return (0);
	read_file(fd, 0);
	close(fd);
//	write(1, "\n", 1);
}
*/
