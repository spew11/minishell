/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.seoul42.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:14:14 by eunjilee          #+#    #+#             */
/*   Updated: 2022/03/28 16:07:19 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*arr;
	int		start;
	int		end;

	if (!s1 || !set)
		return (0);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	if ((size_t)start == ft_strlen(s1))
		arr = (char *)ft_calloc(1, sizeof(char));
	else
	{
		while (s1[end] && ft_strrchr(set, s1[end]))
			end--;
		arr = ft_substr(s1, start, end - start + 1);
	}
	return (arr);
}
