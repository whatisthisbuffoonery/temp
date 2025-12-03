/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_mand.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 06:06:53 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/02 23:25:32 by dthoo            ###   ########.fr       */
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

typedef struct s_flags
{
	char			plus_space;
	char			minus_zero;
	char			hex;
	int				width;
	int				precision;
}					t_flags;

typedef struct s_queue
{
	struct s_queue	*next;
	char			*str;
	t_flags			*flags;
	t_type			type;
	char			arg;
}					t_queue;

int		ft_printf(const char *format, ...);

int		enq(t_queue **q, t_queue *new);
t_queue	*q_new(void);
void	clear_q(t_queue **q, char *ret);
char	*char_op(unsigned int c, t_queue *q, t_list **null, int index);
char	*ptr_op(uintptr_t src, char type, t_queue *q);
char	*uint_op(uintptr_t n, char type, t_queue *q);
char	*int_op(long long n, t_queue *q);

#endif
