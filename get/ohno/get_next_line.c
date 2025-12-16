/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 23:10:52 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/17 02:59:14 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include <unistd.h>

//void ft_putnbr(int n);

char	*read_buf(t_var *file, int fd, int *done)
{
	ssize_t	i;
	ssize_t	k;
	char	*ret;

	k = -1;
	if (file->count >= file->lim || fd != file->fd)//if buffer used or file change
		refresh_buffer(file, fd);
	if (file->lim < 1)//err or eof
		return ((*done = file->lim + !file->lim), NULL);//if 0, 1. if -1, -1
	i = file->count;//41 or less
	while (file->count < file->lim && file->buf[file->count] != '\n')//hm
		file->count ++;
	*done = (file->count < file->lim && file->buf[file->count] == '\n');//if count == 42, not done
	file->count += *done;//exclude !read
	ret = malloc(((file->count - i) + 1) * sizeof(char));
	if (!ret)
		return ((*done = -1), NULL);
	while (i + ++k < file->count)
		ret[k] = file->buf[i + k];
	ret[k] = '\0';
	return (ret);
}

void gnl_test(char *a, int i)
{
	write(1, " | ", 3);
	if (a && a[0])
		write(1, a, i);
	if (!a)
		write(1, "(null)", 6);
	if (!a[0])
		write(1, "(empty)", 7);
	write(1, " | ", 3);
}

int	gnl_new(t_gnllist **lst, char *ret, int *done)
{
	t_gnlnode	*new;
	int			i;

	new = malloc(sizeof(t_gnlnode));
	if (!new)
		return ((*done = -1), 0);
	new->str = ret;
	new->next = NULL;
	i = 0;
	while (ret[i])
		i ++;
	if (*lst)
		(*lst)->tail->next = new;
	if (!*lst)
	{
		*lst = malloc(sizeof(t_gnllist));
		if (!*lst)
			return ((*done = -1), 0);
		(*lst)->head = new;
		(*lst)->node_count = 0;
	}
	(new)->str_len = i;
	(*lst)->node_count += 1;
	(*lst)->tail = new;
	gnl_test(ret, i);
	return (0);
}

int	gnl_shove(t_gnllist *lst, char **ret)
{
	int			i;
	int			k;
	t_gnlnode	*curr;

	*ret = NULL;
	curr = lst->head;
	i = 0;
	while (curr)
	{
		i += curr->str_len;
		curr = curr->next;
	}
	*ret = malloc((i + 1) * sizeof(char));
	if (!*ret)
		return (-1);
	i = 0;
	curr = lst->head;
	while (curr)
	{
		k = -1;
		while (curr->str[++k])
			(*ret)[i + k] = curr->str[k];
		i += k;
		curr = curr->next;
	}
	(*ret)[i] = '\0';
	return (1);
}

void	gnl_cleanup(t_gnllist *lst, char **ret, t_var *file, int done)
{
	t_gnlnode	*curr;
	t_gnlnode	*tmp;

	if (!lst)
	{
		if (done < 0)
		{
			if (*ret)
				free(*ret);
			file->count = 0;
			file->lim = 0;
			*ret = NULL;
		}
		return ;
	}
	curr = lst->head;
	while (curr)
	{
		if (curr->str && curr->str != *ret)
			free(curr->str);
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	if (done < 0)
	{
		if (*ret)
			free(*ret);
		file->count = 0;
		file->lim = 0;
		*ret = NULL;
	}
	free(lst);
}
char	*get_next_line(int fd)
{
	static t_var	file;//you wanna just do the static arr for mand? 
	t_gnllist		*lst;
	char			*ret;
	int				done;

	done = 0;
	lst = NULL;
	ret = NULL;
	while (!done)// no more var space, -1 is err
	{
		ret = read_buf(&file, fd, &done);//set done on \n or !read pls	
		if (!ret)
			break ;
		gnl_new(&lst, ret, &done);//change it later and move this up two lines
	}
	if (done == 1 && lst)
		done = gnl_shove(lst, &ret);
	gnl_cleanup(lst, &ret, &file, done);//can be shoved in here...?
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
	if (a[i - 1])
		;
	ft_putnbr(i);
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
