/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_cmd_info_arr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:37:47 by root              #+#    #+#             */
/*   Updated: 2022/12/18 16:37:47 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parse.h"

static void	init_para(int *p_cmd_i, int *cnt)
{
	*p_cmd_i = 0;
	cnt[ARGC] = 0;
	cnt[REDIR] = 0;
	cnt[HERE] = 0;
}

static int	pipe_err(int *cnt, char *token, char **err_str)
{
	if (!cnt[ARGC] && !cnt[REDIR])
	{
		*err_str = token;
		return (0);
	}
	return (1);
}

static int	check_redir_err(char *token, char **err_str)
{
	if (is_redir(token) || is_pipe(token))
	{
		*err_str = token;
		return (1);
	}
	return (0);
}

static int	append_here_list(t_list **here_list, char *token)
{
	char	*delim;
	t_list	*new;

	delim = ft_strdup(token);
	if (!delim)
		return (0);
	new = ft_lstnew(delim);
	if (!new)
	{
		free(delim);
		return (0);
	}
	ft_lstadd_back(here_list, new);
	return (1);
}

// stntax_err -> err_str != NULL (but not malloc) return (0)
// malloc_err -> return (0)
// success -> return (1)
int	malloc_cmd_info_arr(t_cmd_info **cmd_info_arr, t_list *cur, \
	t_list **here_list, char **err_str)
{
	int	cmd_i;
	int	cnt[3];

	init_para(&cmd_i, cnt);
	while (cur)
	{
		if (is_pipe(cur->content) && (!pipe_err(cnt, cur->content, err_str) || \
			!init_cmd_info(cmd_info_arr, cmd_i++, cnt)))
			return (0);
		else if (is_redir(cur -> content))
		{
			if ((cur->next && check_redir_err(cur->next->content, err_str)) || \
				(is_here(cur -> content) && cur->next && ++cnt[HERE] && \
				!append_here_list(here_list, cur->next->content)))
				return (0);
			if (++cnt[REDIR] && cur->next)
				cur = cur -> next;
		}
		else if (!is_pipe(cur->content))
			cnt[ARGC] += 1;
		cur = cur -> next;
	}
	if (!init_cmd_info(cmd_info_arr, cmd_i, cnt))
		return (0);
	return (1);
}
