/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.seoul42.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:04:01 by eunjilee          #+#    #+#             */
/*   Updated: 2022/03/28 20:31:14 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	char_order(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\r'
		|| c == '\f')
		return (1);
	else if (c == '-' || c == '+')
		return (2);
	else if (c >= '0' && c <= '9')
		return (3);
	else
		return (4);
}

int	ft_atoi(const char *str)
{
	int		order;
	long	num;
	int		sign;

	order = 0;
	str--;
	sign = 1;
	num = 0;
	while (char_order(*(++str)) >= order)
	{
		order = char_order(*str);
		if (order == 1)
			continue ;
		else if (order == 2)
		{
			if (*str == '-')
				sign *= -1;
			order = 3;
		}
		else if (order == 3)
			num = (num * 10) + *str - '0';
		else
			break ;
	}
	return ((int)(num * sign));
}
