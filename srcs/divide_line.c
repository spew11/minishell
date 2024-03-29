/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:31:06 by root              #+#    #+#             */
/*   Updated: 2022/12/18 16:31:30 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parse.h"

static void	init_para(t_list **p_lst, int *num1, int *num2, int *num3)
{
	if (p_lst)
		*p_lst = NULL;
	if (num1)
		*num1 = 0;
	if (num2)
		*num2 = 0;
	if (num3)
		*num3 = 0;
}

static int	count_pipe(t_list *token_list)
{
	t_list	*cur;
	int		pipe_num;

	cur = token_list;
	pipe_num = 0;
	while (cur)
	{
		if (!ft_strncmp(cur->content, "|", 2))
			pipe_num += 1;
		cur = cur -> next;
	}
	return (pipe_num);
}

static int	is_new_token(char *str, int jdx, char *buff)
{
	if (str[jdx] == '|')
		return (1);
	else if (str[jdx] == '<')
	{
		if (!ft_strncmp(buff, "<", 2))
			return (0);
		return (1);
	}
	else if (str[jdx] == '>')
	{
		if (!ft_strncmp(buff, ">", 2))
			return (0);
		return (1);
	}
	if (is_redir(buff) || !ft_strncmp(buff, "|", 2))
		return (1);
	return (0);
}

static int	get_token_from_spl(t_list **token_list, char *str)
{
	char	*buff;
	int		str_i;
	int		buf_i;
	int		quote_flag;

	buff = malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_bzero(buff, sizeof(char) * (ft_strlen(str) + 1));
	if (!buff)
		return (0);
	init_para(NULL, &str_i, &buf_i, &quote_flag);
	while (str[str_i])
	{
		if (buf_i && !quote_flag && is_new_token(str, str_i, buff) \
			&& !buff_to_list(buff, &buf_i, token_list))
			return (0);
		if (!quote_flag && (str[str_i] == '\'' || str[str_i] == '\"'))
			quote_flag = str[str_i];
		else if (quote_flag == str[str_i])
			quote_flag = 0;
		buff[buf_i++] = str[str_i++];
	}
	if (!buff_to_list(buff, &buf_i, token_list))
		return (0);
	free(buff);
	return (1);
}

// malloc_err -> NULL
// succcess -> token_list
t_list	*divide_line_into_token(char *line, int *pipe_num)
{
	t_list	*token_list;
	t_list	*spl_list;
	t_list	*cur_spl;

	spl_list = split_by_space(line);
	if (!spl_list)
		return (NULL);
	token_list = NULL;
	cur_spl = spl_list;
	while (cur_spl)
	{
		if (!get_token_from_spl(&token_list, (char *)(cur_spl->content)))
		{
			ft_lstclear(&spl_list, ft_free);
			return (NULL);
		}
		cur_spl = cur_spl->next;
	}
	ft_lstclear(&spl_list, ft_free);
	*pipe_num = count_pipe(token_list);
	return (token_list);
}
