/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:40:29 by root              #+#    #+#             */
/*   Updated: 2022/12/18 16:47:31 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parse.h"

static void	unclosed_quote_err(t_list **spl_list)
{
	ft_putendl_fd("unclosed quote err", 2);
	ft_lstclear(spl_list, ft_free);
	*spl_list = NULL;
}

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

static int	is_space(char ch)
{
	if ((9 <= ch && 13 >= ch) || ch == 32)
		return (1);
	return (0);
}

static int	add_spl(t_list **spl_list, char *line, int start_i, int line_i)
{
	char	*spl;
	t_list	*new;

	spl = ft_substr(line, start_i, line_i - start_i);
	if (!spl)
	{
		ft_lstclear(spl_list, ft_free);
		return (0);
	}
	new = ft_lstnew(spl);
	if (!new)
	{
		free(spl);
		ft_lstclear(spl_list, ft_free);
		return (0);
	}
	ft_lstadd_back(spl_list, new);
	return (1);
}

t_list	*split_by_space(char *line)
{
	t_list	*spl_list;
	int		start_i;
	int		line_i;
	int		quote_flag;

	init_para(&spl_list, &start_i, &line_i, &quote_flag);
	while (line[line_i])
	{
		if (!quote_flag && is_space(line[line_i]))
		{
			if (start_i != line_i && !add_spl(&spl_list, line, start_i, line_i))
				return (NULL);
			start_i = line_i + 1;
		}
		else if (!quote_flag && (line[line_i] == '\"' || line[line_i] == '\''))
			quote_flag = line[line_i];
		else if (quote_flag == line[line_i])
			quote_flag = 0;
		line_i++;
	}
	if (quote_flag)
		unclosed_quote_err(&spl_list);
	else if (start_i != line_i && !add_spl(&spl_list, line, start_i, line_i))
		return (NULL);
	return (spl_list);
}
