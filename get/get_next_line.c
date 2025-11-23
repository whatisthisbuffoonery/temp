/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 23:10:52 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/23 23:35:47 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static int	n;
	static char	buffer[BUFFER_SIZE];
	char		*ret;
	int 		i;
	int 		start;
	int			lim;
	int			len;

	i = n % BUFFER_SIZE;
	start = i;
	if (!n)
		lim = read(fd, buffer, BUFFER_SIZE);
	while (buffer[i] != '\n' && i < lim)
		i ++;
	if (i < lim && buffer[i] == '\n')
		i ++;
	len = i - start;
	ret = malloc((len + 1) * sizeof(char));
	i = -1;
	while (++i < len)
		ret[i] = buffer[start + i];
	n += len + start;
	ret[i] = '\0';
	if (lim == BUFFER_SIZE && start + len >= lim)
		return (get_strjoin(ret, get_next_line(fd)));
	return (ret);
}

#include <fcntl.h>

void ft_putstr(char *a)
{
	int i = 0;
	while (a[i])
		i ++;
	write(1, a, i);
}

int main(int c, char **v)
{
	if (c < 2)
		return (1);
	int fd = open(v[1], O_RDONLY);
	if (fd < 0)
		return (1);
	char *a = (char *) 1;
	while (a)
	{
		a = get_next_line(fd);
		if (!a)
			return (0);
		ft_putstr(a);
		free(a);
	}
	close(fd);
	write(1, "\n", 1);
}
