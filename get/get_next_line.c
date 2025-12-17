/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 23:10:52 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/17 14:02:55 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
void	probe(char *a, int b, ssize_t c, ssize_t e)
{
	char d;
	if (a)
		write(1, " ye a ", 5);
	if (b)
		write(1, " ye b ", 5);
	ssize_t t = 1;
	if (c < 0)
	{
		write(1, "-", 1);
		c = 0 - c;
	}
	while (c / t > 9)
		t *= 10;
	while (t)
	{
		d = ((c / t) % 10) + 48;
		write(1, &d, 1);
		t /= 10;
	}
	t = 1;
	write(1, " | ", 3);
	if (e < 0)
	{
		write(1, "-", 1);
		e = 0 - e;
	}
	while (e / t > 9)
		t *= 10;
	while (t)
	{
		d = ((e / t) % 10) + 48;
		write(1, &d, 1);
		t /= 10;
	}
}
*/
char	*read_buf(t_var *file, int fd, int *done)
{
	ssize_t	i;
	ssize_t	k;
	char	*ret;

	k = -1;
	if (file->count >= file->lim || fd != file->fd)
		refresh_buffer(file, fd);
	if (file->lim < 1)
		return ((*done = file->lim + !file->lim), NULL);
	i = file->count;
	while (file->count < file->lim && file->buf[file->count] != '\n')
		file->count ++;
	*done = (file->count < file->lim && file->buf[file->count] == '\n');
	file->count += *done;
	ret = malloc(((file->count - i) + 1) * sizeof(char));
	if (!ret)
	{
		file->count = i;
		file->lim = -1;
		return (NULL);
	}
	while (i + ++k < file->count)
		ret[k] = file->buf[i + k];
	ret[k] = '\0';
	return (ret);
}

void ret_emit(char *ret)
{
	int i;

	i = 0;
	if (ret)
	{
		write(1, "[", 1);
		while (ret[i])
			i ++;
		write(1, ret, i);
		write(1, "]", 1);
	}
	else
		write(1, "n", 1);
}

char	*get_next_line(int fd)
{
	static t_var	file;
	char			*ret;
	char			*tmp;
	int				done;

	done = 0;
	ret = read_buf(&file, fd, &done);
	while (ret && !done && file.lim > 0)
	{
		tmp = read_buf(&file, fd, &done);
		if (!tmp)
		{
			if (file.lim == 0)
				break ;
			free(ret);
			file.lim = 0;
			file.count = 0;
			return (NULL);
		}
		done += get_strjoin(&ret, tmp, 0, 0);//try to phase out for a faster solution
	}
	ret_emit(ret);
	return (ret);
}
/*
#include <fcntl.h>

void ft_putstr(char *a, int flag)
{
	int i = 0;
	if (!a)
	{
		ft_putstr("(null)\n", 0);
		return ;
	}
	while (a[i])
		i ++;
	write(1, a, i);
	if (flag)
	{
		if (a[i - 1] == '\n')
			write(1, "nl\n", 3);
		else
			write(1, "empty\n", 6);
	}
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
			ft_putstr("nl\n", 0);
		if (a && a[0] == '\0')
			ft_putstr(".\n", 0);
		
		ft_putstr(a, 1);
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
	read_file(fd, 0);
//	close(fd);
//	fd = open("not_a_file.txt", O_WRONLY);
//	fd = -100;
//	read_file(fd, 0);
//	fd = open(v[1], O_RDONLY);
//	if (fd < 0)
//		return (0);
	read_file(fd, 0);
	read_file(fd, 0);
	read_file(fd, 0);
	read_file(fd, 0);
	read_file(fd, 0);
	close(fd);
//	write(1, "\n", 1);
}
*/
