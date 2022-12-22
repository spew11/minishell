/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:06:40 by eunjilee          #+#    #+#             */
/*   Updated: 2022/12/22 15:52:30 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_cmd_without_pipe(t_cmd_info *cmd_infos, int idx,
		t_externs *externs)
{
	int	temp[2];

	temp[0] = dup(0);
	temp[1] = dup(1);
	g_exit_status = run_cmd(cmd_infos + idx, externs);
	dup2(temp[0], 0);
	dup2(temp[1], 1);
	return ;
}

static void	close_fds(int pipe_num, int idx, t_shell_info *shell_info)
{
	if (idx > 0)
	{
		close(shell_info->in_fd);
	}
	if (idx < pipe_num)
	{
		shell_info->in_fd = shell_info->out_fd[0];
		close(shell_info->out_fd[1]);
	}
	return ;
}

static int	run_cmd_with_pipe(t_cmd_info *cmd_infos, int pipe_num, int idx,
	t_shell_info *shell_info)
{
	shell_info->pid_arr[idx] = fork();
	if (shell_info->pid_arr[idx] < 0)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	if (shell_info->pid_arr[idx] == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (idx < pipe_num)
		{
			dup2(shell_info->out_fd[1], 1);
			close(shell_info->out_fd[0]);
		}
		if (shell_info->in_fd != -1)
		{
			dup2(shell_info->in_fd, 0);
			close(shell_info->in_fd);
		}
		exit(run_cmd(cmd_infos + idx, shell_info->externs));
	}
	else
		close_fds(pipe_num, idx, shell_info);
	return (0);
}

int	run_cmds(t_cmd_info *cmd_infos, int pipe_num, t_shell_info *shell_info)
{
	int	idx;

	shell_info->in_fd = -1;
	shell_info->pid_arr = (int *)malloc(sizeof(int) * (pipe_num + 1));
	null_guard_arr2(shell_info->pid_arr);
	idx = 0;
	while (idx <= pipe_num)
	{
		if (idx < pipe_num)
			pipe(shell_info->out_fd);
		if (pipe_num == 0)
			run_cmd_without_pipe(cmd_infos, idx, shell_info->externs);
		else
			if (run_cmd_with_pipe(cmd_infos, pipe_num, idx, shell_info))
				return (1);
		idx++;
	}
	wait_pids(shell_info->pid_arr, pipe_num);
	unlink_tmpfiles(cmd_infos, pipe_num);
	free(shell_info->pid_arr);
	return (0);
}
