/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:37:28 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/21 19:18:53 by dthoo            ###   ########.fr       */
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
# define ERR 5

int	handle_flag(const char *format, int *i, int *flag, t_tables *table);

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
