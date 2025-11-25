/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:37:28 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/26 00:33:40 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

# define PERCENT 1
# define HASH 2
# define PLUS 4
# define SPACE 8
# define DASH 16
# define ZERO 32
# define DOT 64
# define ERR 128
# define NO_OP 256

char		print_ptr(char type, char *src);
static void	tabler(char *table, int *i, char **ret);
char		*print_base_signed(intptr_t n, char type);

typedef union s_param
{
	int		a;
	char	c;
	char	*p;
}			t_param;

typedef struct s_tables
{
	unsigned char	type[256];
	unsigned char	flag[256];
	t_flags			flags;
}					t_tables;

#endif
