/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.seoul42.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:13:31 by eunjilee          #+#    #+#             */
/*   Updated: 2022/03/22 19:28:22 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*arr;
	int		arr_len;

	if (!s1 || !s2)
		return (0);
	arr_len = ft_strlen(s1) + ft_strlen(s2);
	arr = (char *)malloc(sizeof(char) * (arr_len + 1));
	if (!arr)
		return (0);
	arr[0] = '\0';
	ft_strlcat(arr, (char *)s1, arr_len + 1);
	ft_strlcat(arr, (char *)s2, arr_len + 1);
	return (arr);
}
