/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 22:15:13 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/24 02:08:05 by dthoo            ###   ########.fr       */
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
	int		count;
	int		lim;
}			t_var;

char	*get_next_line(int fd);
char	*get_strjoin(char *a, char *b);
int		get_condition(t_var *buffer, int start, int len);
int		refresh_buffer(t_var *buffer, int fd, int *me_fd);

#endif
