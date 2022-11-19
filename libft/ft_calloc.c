/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.seoul42.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:11:22 by eunjilee          #+#    #+#             */
/*   Updated: 2022/04/04 13:52:51 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*array;
	size_t	i;

	array = malloc(size * count);
	if (!array)
		return (0);
	i = 0;
	while (i < (size * count))
	{
		((unsigned char *)array)[i] = 0;
		i++;
	}
	return (array);
}
