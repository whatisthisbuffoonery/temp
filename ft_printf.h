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

# ifdef BONUS

int	bonus(void);

#  define BONUS handle_flag
# endif

# ifndef BONUS
#  define BONUS 0
# endif

typedef struct s_flags
{
	char	minus_stack;
	char	plus_stack;
	char	dot;
	char	hash;
	char	type;
}			t_flags;

typedef struct s_tables
{
	unsigned char	type[256];
	unsigned char	flag[256];
	t_flags			flags;
}					t_tables;

#endif
