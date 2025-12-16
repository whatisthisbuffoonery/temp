/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_printf.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dthoo <dthoo@student.42singapore.sg>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/11/26 02:17:50 by dthoo			   #+#	  #+#			  */
/*	 Updated: 2025/11/26 06:12:51 by dthoo			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "ft_printf.h"

void	printf_tokens(const char *format, t_queue **q, int size);
char	*process(t_queue *q, va_list *va, int *len);

static void	printf_init(t_queue **q, int *return_value, char **ret)
{
	*return_value = 0;
	*q = NULL;
	*ret = NULL;
}

int	ft_printf(const char *format, ...)
{
	va_list	va;
	char	*ret;
	t_queue	*q;
	int		return_value;

	printf_init(&q, &return_value, &ret);
	va_start(va, format);
	printf_tokens(format, &q, ft_strlen(format));
	if (q)
		ret = process(q, &va, &return_value);
	clear_q(&q, ret);
	if (ret)
	{
		write(1, ret, return_value);
		free(ret);
	}
	va_end(va);
	return (return_value);
}
