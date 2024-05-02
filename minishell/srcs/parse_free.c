/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:38:15 by root              #+#    #+#             */
/*   Updated: 2022/12/18 16:38:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	array_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	redir_free(t_redir *redir, int redir_num)
{
	int	i;

	i = 0;
	while (i < redir_num + 1)
	{
		if (redir[i].str)
			free(redir[i].str);
		i++;
	}
	free(redir);
}

void	cmd_info_free(t_cmd_info **cmd_info_arr, int pipe_num)
{
	int	i;

	i = 0;
	while (i < pipe_num + 1)
	{
		if ((*cmd_info_arr)[i].argv)
			array_free((*cmd_info_arr)[i].argv);
		if ((*cmd_info_arr)[i].redir)
			redir_free((*cmd_info_arr)[i].redir, \
			(*cmd_info_arr)[i].redir_num);
		if ((*cmd_info_arr)[i].here)
			array_free((*cmd_info_arr)[i].here);
		i++;
	}
	free(*cmd_info_arr);
	*cmd_info_arr = NULL;
}

int	buff_free(char *buff)
{
	if (buff)
		free(buff);
	return (SYS);
}
