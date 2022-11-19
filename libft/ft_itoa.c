/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.seoul42.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:12:09 by eunjilee          #+#    #+#             */
/*   Updated: 2022/03/28 20:30:28 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fill_array(int n, char *array, int rdx, long num)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		array[0] = '-';
		i++;
	}
	while (rdx)
	{
		array[i] = num / rdx + '0';
		num -= (num / rdx) * rdx;
		rdx /= 10;
		i++;
	}
	array[i] = '\0';
	return (array);
}

char	*ft_itoa(int n)
{
	char	*array;
	int		size;
	int		rdx;
	long	num;

	size = 1;
	rdx = 1;
	num = n;
	if (n < 0)
	{
		size++;
		num *= -1;
	}
	while (num / rdx >= 10)
	{
		rdx *= 10;
		size++;
	}
	array = (char *)malloc(sizeof(char) * (size + 1));
	if (!array)
		return (0);
	array = fill_array(n, array, rdx, num);
	return (array);
}
