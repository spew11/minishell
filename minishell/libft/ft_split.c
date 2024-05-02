/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.seoul42.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:13:09 by eunjilee          #+#    #+#             */
/*   Updated: 2022/03/28 20:31:36 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_next_c(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int	get_word_cnt(const char *str, char c)
{
	int	word_cnt;
	int	i;

	i = 0;
	word_cnt = 0;
	while (str[i])
	{
		i += is_next_c(str + i, c);
		word_cnt++;
		while (str[i] && str[i] == c)
			i++;
	}
	return (word_cnt);
}

static char	*get_word(char **arr, const char *str, int len)
{
	char	*array;
	int		i;

	array = (char *)malloc(sizeof(char) * (len + 1));
	if (!array)
	{
		i = -1;
		while (arr[++i])
			free(arr[i]);
		free(arr);
		return (0);
	}
	i = -1;
	while (++i < len)
	{
		array[i] = str[i];
	}
	array[i] = '\0';
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		arr_idx;
	int		i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	arr = (char **)malloc(sizeof(char *) * (get_word_cnt(s + i, c) + 1));
	if (!arr)
		return (0);
	arr_idx = 0;
	while (s[i])
	{
		arr[arr_idx++] = get_word(arr, s + i, is_next_c(s + i, c));
		if (!arr[arr_idx - 1])
			return (0);
		i += is_next_c(s + i, c);
		while (s[i] && s[i] == c)
			i++;
	}
	arr[arr_idx] = 0;
	return (arr);
}
