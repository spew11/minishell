/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:07:03 by eunjilee          #+#    #+#             */
/*   Updated: 2022/12/17 17:54:14 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	null_guard_double_arr(char **arr)
{
	if (!arr)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	return ;
}

void	null_guard_arr(char *arr)
{
	if (!arr)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	return ;
}

void	free_double_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return ;
}

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", -1) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", -1) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", -1) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", -1) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", -1) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", -1) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", -1) == 0)
		return (1);
	return (0);
}

int	exec_builtin(int argc, char *argv[],
		t_var_lst **env_lst, t_var_lst **export_lst)
{
	if (ft_strncmp(argv[0], "echo", -1) == 0)
		return (echo(argc, argv));
	if (ft_strncmp(argv[0], "cd", -1) == 0)
		return (cd(argc, argv, *env_lst));
	if (ft_strncmp(argv[0], "pwd", -1) == 0)
		return (pwd());
	if (ft_strncmp(argv[0], "export", -1) == 0)
		return (export(argc, argv, env_lst, export_lst));
	if (ft_strncmp(argv[0], "unset", -1) == 0)
		return (unset(argc, argv, env_lst, export_lst));
	if (ft_strncmp(argv[0], "env", -1) == 0)
		return (env(argc, *env_lst));
	if (ft_strncmp(argv[0], "exit", -1) == 0)
		(ft_exit(argc));
	return (1);
}
