/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:14:33 by eunjilee          #+#    #+#             */
/*   Updated: 2022/03/29 15:31:34 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstclear2(t_list **lst)
{
	t_list	*now;
	t_list	*tmp;

	if (!*lst || !lst)
		return ;
	now = *lst;
	while (now)
	{
		tmp = now;
		now = now->next;
		free(tmp);
	}
	*lst = 0;
	return ;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_head;

	if (!lst || !f)
		return (0);
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (0);
	new_head = new;
	while (lst->next)
	{
		lst = lst->next;
		new->next = ft_lstnew(f(lst->content));
		if (!new)
		{
			if (!del)
				ft_lstclear2(&new_head);
			else
				ft_lstclear(&new_head, del);
			return (0);
		}
		new = new->next;
	}
	return (new_head);
}
