/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_text_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:34:25 by root              #+#    #+#             */
/*   Updated: 2022/12/18 16:48:52 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parse.h"

static int	set_quote(int *quote, char ch)
{
	*quote = (int)ch;
	return (1);
}

static char	*expand_env(char *substr, int *str_i, t_var_lst *env_lst)
{
	t_var_lst	*cur;
	int			len;

	if (substr[0] == '?')
	{
		*str_i += 1;
		return (ft_itoa(g_exit_status));
	}
	len = 0;
	if (!ft_isalpha(substr[len]))
		return (ft_strdup(""));
	while (ft_isalpha(substr[len]) || ft_isalnum(substr[len]) || \
			substr[len] == '_')
		len++;
	*str_i += len;
	cur = env_lst;
	while (cur)
	{
		if (!strncmp(substr, cur->var, len) && cur->var[len] == '\0')
			return (ft_strdup(cur->val));
		cur = cur->next;
	}
	return (ft_strdup(""));
}

static int	env_to_list(t_list **text_list, char *str, \
			int *str_i, t_var_lst *env_lst)
{
	char	*env_str;
	t_list	*new;

	env_str = expand_env(str + *str_i + 1, str_i, env_lst);
	if (!env_str)
		return (SYS);
	new = ft_lstnew(env_str);
	if (!new)
	{
		free(env_str);
		return (SYS);
	}
	ft_lstadd_back(text_list, new);
	return (NONE);
}

static int	add_buf(char **buff, int *buf_i, t_list **text_list, int *err)
{
	if (!buff_to_list(*buff, buf_i, text_list))
	{
		*err = SYS;
		*buff = NULL;
		return (0);
	}
	*err = NONE;
	return (1);
}

int	get_text_list(t_list **text_list, char *buff, char *str, t_var_lst *env_lst)
{
	int	si;
	int	bi;
	int	quote;
	int	err;

	si = 0;
	bi = 0;
	quote = 0;
	err = 0;
	while (str[si])
	{
		if ((!quote && is_quote(str[si]) && set_quote(&quote, str[si])) || \
			(quote == str[si] && set_quote(&quote, 0)))
			add_buf(&buff, &bi, text_list, &err);
		else if (is_env(quote, str[si]) && add_buf(&buff, &bi, text_list, &err))
			err = env_to_list(text_list, str, &si, env_lst);
		else if (err == NONE)
			buff[bi++] = str[si];
		if (err)
			return (buff_free(buff));
		si++;
	}
	if (!buff_to_list(buff, &bi, text_list))
		return (SYS);
	return (NONE);
}
