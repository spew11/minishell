/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:37:23 by root              #+#    #+#             */
/*   Updated: 2022/12/18 16:37:24 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parse.h"

int	is_pipe(char *token)
{
	if (!ft_strncmp(token, "|", 2))
		return (1);
	return (0);
}

int	is_redir(char *str)
{
	if (!ft_strncmp(str, "<", 2))
		return (1);
	if (!ft_strncmp(str, "<<", 3))
		return (1);
	if (!ft_strncmp(str, ">", 2))
		return (1);
	if (!ft_strncmp(str, ">>", 3))
		return (1);
	return (0);
}

int	is_here(char *token)
{
	if (!ft_strncmp(token, "<<", 3))
		return (1);
	return (0);
}

int	is_quote(char ch)
{
	if (ch == '\'' || ch == '\"')
		return (1);
	return (0);
}

int	is_env(int quote, char ch)
{
	if (ch == '$' && (quote != '\''))
		return (1);
	return (0);
}
