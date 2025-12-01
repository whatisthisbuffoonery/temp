/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 06:06:53 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/01 19:47:38 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdint.h>

typedef enum s_type
{
	str,
	op,
	nil
}	t_type;

typedef struct s_flags
{
	char			plus;
	char			minus;
	char			hex;
	int				width;
	int				precision;
}					t_flags;

typedef struct s_queue
{
	struct s_queue	*next;
	t_flags			*flags;
	char			*str;
	t_type			type;
	char			arg;
}					t_queue;

int		ft_printf(const char *format, ...);

int		enq(t_queue **q, t_queue *new);
int		printf_while_help(const char *format, int *i, char *type, char *flag);
t_queue	*q_new(void);
void	clear_q(t_queue **q, char *ret);
char	*char_op(unsigned char c);
char	*ptr_op(char *p, char type);
char	*uint_op(uintptr_t n, char type);
char	*int_op(long long n);

#endif
