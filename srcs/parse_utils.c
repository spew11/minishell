/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:39:40 by root              #+#    #+#             */
/*   Updated: 2022/12/18 16:39:41 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parse.h"

void	ft_free(void *ptr)
{
	free(ptr);
}

void	sig_handler2(int sig_t)
{
	if (sig_t == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		close(0);
		g_exit_status = (-5);
	}
}

int	buff_to_list(char *buff, int *buf_i, t_list **list)
{
	char	*str;
	t_list	*new;

	buff[*buf_i] = '\0';
	str = ft_strdup(buff);
	if (!str)
	{
		ft_lstclear(list, ft_free);
		free(buff);
		return (0);
	}
	new = ft_lstnew(str);
	if (!new)
	{
		ft_lstclear(list, ft_free);
		free(str);
		free(buff);
		return (0);
	}
	ft_lstadd_back(list, new);
	ft_bzero(buff, ft_strlen(buff) + 1);
	*buf_i = 0;
	return (1);
}
