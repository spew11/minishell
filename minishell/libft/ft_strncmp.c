/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.seoul42.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:13:58 by eunjilee          #+#    #+#             */
/*   Updated: 2022/03/28 17:52:11 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	c1;
	unsigned char	c2;

	if (!n)
		return (0);
	i = 0;
	while (i++ < n)
	{
		c1 = (unsigned char)(*s1++);
		c2 = (unsigned char)(*s2++);
		if (!c1 || !c2)
			break ;
		if (c1 != c2)
			break ;
	}
	return (c1 - c2);
}
