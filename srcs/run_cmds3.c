/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:06:49 by eunjilee          #+#    #+#             */
/*   Updated: 2022/12/16 16:53:46 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_tmpfiles(t_cmd_info *cmd_infos, int pipe_num)
{
	int	i;
	int	j;

	i = 0;
	while (i <= pipe_num)
	{
		j = 0;
		while (j < cmd_infos[i].here_num)
		{
			if (unlink(cmd_infos[i].here[j]) < 0)
			{
				g_exit_status = -1;
			}
			j++;
		}
		i++;
	}
	return ;
}

void	wait_pids(pid_t *pid_arr, int pipe_num)
{
	int	status;
	int	idx;

	if (pipe_num > 0)
	{
		if (waitpid(pid_arr[pipe_num], &status, 0) != pid_arr[pipe_num])
			g_exit_status = -1;
		if (WIFEXITED(status) != 0)
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = WTERMSIG(status) + 128;
		idx = 0;
		while (idx < pipe_num)
		{
			if (waitpid(pid_arr[idx], 0, 0) != pid_arr[idx])
				g_exit_status = -1;
			idx++;
		}
	}
	return ;
}
