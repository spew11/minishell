/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:39:10 by root              #+#    #+#             */
/*   Updated: 2022/12/18 17:21:35 by root             ###   ########.fr       */
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
	perror("minishell");
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
	if (err == SYN)
		return (ft_syn_err(&token_list, &cmd_info_arr, *pipe_num, &tmp_list));
	if (err == SYS)
		return (sys_call_err(&token_list, &cmd_info_arr, *pipe_num, &tmp_list));
	err = fill_cmd_info_arr(cmd_info_arr, token_list, tmp_list, env_lst);
	if (err == SYN)
		return (ft_syn_err(&token_list, &cmd_info_arr, *pipe_num, &tmp_list));
	if (err == SYS)
		return (sys_call_err(&token_list, &cmd_info_arr, *pipe_num, &tmp_list));
	ft_clear_list(&token_list, &tmp_list);
	print_cmd_arr(cmd_info_arr, *pipe_num);
	return (cmd_info_arr);
}
