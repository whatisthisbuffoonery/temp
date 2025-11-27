/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 06:06:53 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/26 06:10:50 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAND_HEADER_H
# define MAND_HEADER_H

# include <libft.h>
# include <stdarg.h>
# include <stdint.h>

typedef enum
{
	str,
	op,
	nil
}	t_type;

typedef struct s_queue
{
	struct s_queue	*next;
	char			*str;
	t_type			type;
}					t_queue;

int		enq(t_queue **q, t_queue *new);
t_queue	q_new(void);
void	clear_q(t_queue **q);
char	*char_op(unsigned char c);
char	*ptr_op(char *p, char type);
char	*uint_op(uintptr_t n, char type);
char	*int_op(long long n);

#endif
