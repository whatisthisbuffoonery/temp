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
char	*process(t_queue *q, va_list *va, t_list **null);

static void	printf_init(t_queue **q, t_list **null, int *return_value, char **ret)
{
	*return_value = 0;
	*q = NULL;
	*null = NULL;
	*ret = NULL;
}
//handle the flag thingy later. t_list has the arg node in content2
static int	printf_write(char *ret, t_list *null)
{
	int		i;
	int		start;
	t_list	*curr;

	i = 0;
	start = 0;
	curr = null;
	while (curr)
	{
		while (i < *(int *) curr->content)
			i ++;
		if (i > start)
			write(1, &ret[start], i - start);
		write(1, "\0", 1);
		curr = curr->next;
		start = i;
	}
	ft_putstr_fd(&ret[i], 1);
	i = ft_strlen(ret);
	return (i + ft_lstsize(null));
}


int	ft_printf(const char *format, ...)//actual string production TBA
{
	va_list	va;
	char	*ret;
	t_queue	*q;
	t_list	*null_list;
	int		return_value;

	printf_init(&q, &null_list, &return_value, &ret);
	va_start(va, format);
	printf_tokens(format, &q, ft_strlen(format));//signal: q == null
	if (q)
		ret = process(q, &va, &null_list);//signal: ret == null, maybe needs a crash flag
	if (ret)
		return_value = printf_write(ret, null_list);
//	else if (ft_strlen(format) > 0)
//		write(1, "where ret\n", 10);
	clear_q(&q, ret);
	free(ret);
	va_end(va);
	ft_lstclear(&null_list, free);
	return (return_value);
}
