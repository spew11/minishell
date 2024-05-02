/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:39:10 by root              #+#    #+#             */
/*   Updated: 2022/12/19 17:48:29 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	ft_clear_list(t_list **token_list, t_list **tmp_list)
{
	ft_lstclear(token_list, ft_free);
	ft_lstclear(tmp_list, ft_free);
}

static t_cmd_info	*sys_call_err(t_list **token_list, \
			t_cmd_info **cmd_info_arr, int pipe_num, t_list **tmp_list)
{
	if (!token_list)
		return (NULL);
	perror("minishell");
	g_exit_status = 1;
	if (token_list)
		ft_lstclear(token_list, ft_free);
	if (cmd_info_arr)
		cmd_info_free(cmd_info_arr, pipe_num);
	if (tmp_list)
		tmp_clear(tmp_list);
	return (NULL);
}

static t_cmd_info	*ft_syn_err(t_list **token_list, \
			t_cmd_info **cmd_info_arr, int pipe_num, t_list **tmp_list)
{
	g_exit_status = 258;
	ft_lstclear(token_list, ft_free);
	cmd_info_free(cmd_info_arr, pipe_num);
	ft_lstclear(tmp_list, ft_free);
	return (NULL);
}

static t_cmd_info	*sigint_exit(t_list **token_list, \
			t_cmd_info **cmd_info_arr, int pipe_num, t_list **tmp_list)
{
	g_exit_status = 1;
	ft_lstclear(token_list, ft_free);
	cmd_info_free(cmd_info_arr, pipe_num);
	ft_lstclear(tmp_list, ft_free);
	return (NULL);
}

t_cmd_info	*parse_line(char *line, int *pipe_num, t_var_lst *env_lst)
{
	t_cmd_info	*cmd_info_arr;
	t_list		*token_list;
	t_list		*here_list;
	t_list		*tmp_list;
	int			err;

	token_list = divide_line_into_token(line, pipe_num);
	if (!token_list)
		return (sys_call_err(NULL, NULL, 0, NULL));
	cmd_info_arr = init_cmd_info_arr(token_list, *pipe_num, &here_list, &err);
	if (!cmd_info_arr)
		return (sys_call_err(&token_list, NULL, 0, NULL));
	tmp_list = here_doc(here_list, &err);
	ft_lstclear(&here_list, ft_free);
	if (g_exit_status == (-5))
		return (sigint_exit(&token_list, &cmd_info_arr, *pipe_num, &tmp_list));
	if (err == NONE)
		err = fill_cmd_info_arr(cmd_info_arr, token_list, tmp_list, env_lst);
	if (err == SYN)
		return (ft_syn_err(&token_list, &cmd_info_arr, *pipe_num, &tmp_list));
	if (err == SYS)
		return (sys_call_err(&token_list, &cmd_info_arr, *pipe_num, &tmp_list));
	ft_clear_list(&token_list, &tmp_list);
	return (cmd_info_arr);
}
