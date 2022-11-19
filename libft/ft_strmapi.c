/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.seoul42.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:13:53 by eunjilee          #+#    #+#             */
/*   Updated: 2022/04/04 13:59:02 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*arr;
	int				arr_len;
	unsigned int	i;

	if (!s || !f)
		return (0);
	arr_len = ft_strlen(s);
	arr = (char *)malloc(sizeof(char) * (arr_len + 1));
	if (!arr)
		return (0);
	i = 0;
	while (s[i])
	{
		arr[i] = f(i, s[i]);
		i++;
	}
	arr[arr_len] = '\0';
	return (arr);
}
