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

typedef enum
{
	str,
	op
}	t_type;

typedef struct s_queue
{
	struct s_queue	*next;
	char			*str;
	t_type			type;
}					t_queue;

#endif
