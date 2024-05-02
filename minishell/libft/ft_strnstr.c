/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.seoul42.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:14:03 by eunjilee          #+#    #+#             */
/*   Updated: 2022/03/28 14:58:09 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (!*needle || !needle)
		return ((char *)haystack);
	if (!len)
		return (0);
	if (!*haystack || !haystack)
		return (0);
	if ((size_t)ft_strlen(needle) > len)
		return (0);
	if (ft_strlen(needle) > ft_strlen(haystack))
		return (0);
	i = 0;
	while (i <= len - (size_t)ft_strlen(needle) && haystack[i])
	{
		if (!ft_memcmp(haystack + i, needle, ft_strlen(needle)))
			return ((char *)(haystack + i));
		i++;
	}
	return (0);
}
