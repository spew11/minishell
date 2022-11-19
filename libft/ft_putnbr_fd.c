/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.seoul42.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:12:57 by eunjilee          #+#    #+#             */
/*   Updated: 2022/03/28 20:41:20 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_recursive(long num, int fd)
{
	char	c;

	if (num == 0)
		return ;
	c = num % 10 + '0';
	ft_putnbr_recursive(num / 10, fd);
	write(fd, &c, 1);
	return ;
}

void	ft_putnbr_fd(int n, int fd)
{
	long	num;

	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	num = n;
	if (n < 0)
	{
		num *= -1;
		write(fd, "-", 1);
	}
	ft_putnbr_recursive(num, fd);
	return ;
}
