/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:06:44 by eunjilee          #+#    #+#             */
/*   Updated: 2022/12/22 17:08:31 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_input(int *in_fd, char *filename)
{
	if (ft_access(filename) == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	if (*in_fd != -1)
		close(*in_fd);
	*in_fd = open(filename, O_RDONLY, 0644);
	if (*in_fd < 0)
	{
		ft_putendl_fd("Failed to open file", 2);
		return (1);
	}
	dup2(*in_fd, 0);
	return (0);
}

static int	set_output(int *out_fd, int type, char *filename)
{
	if (type == OUTFILE)
	{
		if (*out_fd != -1)
			close(*out_fd);
		*out_fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	else if (type == FILE_APPEND)
	{
		if (*out_fd != -1)
			close(*out_fd);
		*out_fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
	if (*out_fd < 0)
	{
		ft_putendl_fd("Failed to open file", 2);
		return (1);
	}
	dup2(*out_fd, 1);
	return (0);
}

static int	set_io(t_cmd_info *cmd_info, int *in_fd, int *out_fd)
{
	int		type;
	char	*filename;
	int		i;

	*in_fd = -1;
	*out_fd = -1;
	i = 0;
	while (i < cmd_info->redir_num)
	{
		type = cmd_info->redir[i].type;
		filename = cmd_info->redir[i].str;
		if (type == INFILE || type == HERE_DOC)
		{
			if (set_input(in_fd, filename))
				return (1);
		}
		else
		{
			if (set_output(out_fd, type, filename))
				return (1);
		}
		i++;
	}
	return (0);
}

static int	exec_binary(t_cmd_info *cmd_info, t_externs *externs)
{
	int	pid;
	int	status;
	int	ret;

	ret = 0;
	pid = fork();
	if (pid < 0)
		ret = pid_err();
	if (pid == 0)
		ft_execve(cmd_info->argv, externs);
	else
	{
		if (waitpid(pid, &status, 0) != pid)
		{
			ft_putendl_fd(strerror(errno), 2);
			return (-1);
		}
		if (WIFEXITED(status) != 0)
			ret = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			ret = WTERMSIG(status) + 128;
	}
	return (ret);
}

int	run_cmd(t_cmd_info *cmd_info, t_externs *externs)
{
	int	in_fd;
	int	out_fd;
	int	ret;

	if (set_io(cmd_info, &in_fd, &out_fd))
		return (1);
	if (cmd_info->argc == 0)
		ret = 0;
	else
	{
		if (is_builtin(cmd_info->argv[0]))
		{
			ret = exec_builtin(cmd_info->argc, cmd_info->argv,
					&externs->env_lst, &externs->export_lst);
		}
		else
		{
			signal(SIGQUIT, SIG_DFL);
			ret = exec_binary(cmd_info, externs);
			signal(SIGQUIT, SIG_IGN);
		}
	}
	close(in_fd);
	close(out_fd);
	return (ret);
}
