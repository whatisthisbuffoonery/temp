/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 01:14:45 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/20 01:26:31 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstnew_help(void *content)
{
	t_list	*a;

	a = malloc(sizeof(t_list));
	a->next = NULL;
	a->content = content;
	return (a);
}

static void	ft_lstdelone_help(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del && lst->content)
		del(lst->content);
	free(lst);
}

static void	ft_lstclear_help(t_list **lst, void (*del)(void *))
{
	t_list	*f;
	t_list	*tmp;

	if (!lst || !*lst)
		return ;
	f = *lst;
	while (f)
	{
		tmp = f->next;
		ft_lstdelone_help(f, del);
		f = tmp;
	}
	*lst = NULL;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*curr;
	t_list	*tmp;

	head = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		tmp = ft_lstnew_help(f(lst->content));
		lst = lst->next;
		if (!tmp)
			ft_lstclear_help(&head, del);
		if (!tmp)
			return (NULL);
		if (!head)
		{
			head = tmp;
			curr = tmp;
			continue ;
		}
		curr->next = tmp;
		curr = curr->next;
	}
	return (head);
}
