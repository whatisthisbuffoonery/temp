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

#include "header_mand.h"

void	printf_tokens(const char *format, t_queue **q, int size);
char	*process(t_queue *q, va_list va);

int	ft_printf(const char *format, ...)//actual string production TBA
{
	va_list	va;
	char	*ret;
	t_queue	*q;
	int		return_value;

	q = NULL;
	ret = NULL;
	va_start(va, format);
	printf_tokens(format, &q, ft_strlen(format));//signal: q == null
	if (q)
		ret = process(q, va);//signal: ret == null, maybe needs a crash flag
	return_value = (ret != NULL);
	clear_q(&q, ret);
	if (ret)
	{
		ft_putstr_fd(ret, 1);
		free(ret);
	}
	else
		write(1, "where ret\n", 10);
	va_end(va);
	return (return_value);
}
