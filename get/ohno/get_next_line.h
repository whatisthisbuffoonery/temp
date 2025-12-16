/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 22:15:13 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/25 16:48:06 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 1024

# endif

typedef struct s_var
{
	char	buf[BUFFER_SIZE];
	ssize_t	count;
	ssize_t	lim;
	int		fd;
}			t_var;

typedef struct s_gnlnode
{
	char				*str;
	struct s_gnlnode	*next;
	int					str_len;
}						t_gnlnode;

typedef struct s_gnllist
{
	t_gnlnode			*head;
	t_gnlnode			*tail;
	int					node_count;
}						t_gnllist;

char	*get_next_line(int fd);
int		get_strjoin(char **a, char *b, ssize_t i, ssize_t k);
void	refresh_buffer(t_var *file, int fd);

#endif
