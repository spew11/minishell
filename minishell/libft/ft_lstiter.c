/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:12:05 by eunjilee          #+#    #+#             */
/*   Updated: 2022/03/29 14:38:24 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*now;

	if (!lst || !f)
		return ;
	now = lst;
	while (now)
	{
		f(now->content);
		now = now->next;
	}
	return ;
}
