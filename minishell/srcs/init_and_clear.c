/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:09:14 by eunjilee          #+#    #+#             */
/*   Updated: 2022/12/16 16:24:30 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_term(struct termios *term)
{
	tcgetattr(0, term);
	term->c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, term);
	return ;
}

void	init_shell_info(t_shell_info *shell_info, char *envp[])
{
	shell_info->externs = (t_externs *)malloc(sizeof(t_externs) * 1);
	if (!shell_info->externs)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	shell_info->externs->env_lst = init_var_lst(envp);
	shell_info->externs->export_lst = init_var_lst(envp);
	sort_var_lst(shell_info->externs->export_lst);
	shell_info->externs->env_arr = 0;
	return ;
}

void	clear_shell_info(t_shell_info *shell_info)
{
	clear_var_lst(shell_info->externs->env_lst);
	clear_var_lst(shell_info->externs->export_lst);
	free_double_arr(shell_info->externs->env_arr);
	return ;
}
