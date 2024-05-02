/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:06:55 by eunjilee          #+#    #+#             */
/*   Updated: 2022/03/29 15:06:42 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*now;
	t_list	*tmp;

	if (!*lst || !lst)
		return ;
	now = *lst;
	while (now)
	{
		del(now->content);
		tmp = now;
		now = now->next;
		free(tmp);
	}
	*lst = 0;
	return ;
}
