#include "./parse.h"

static int	set_quote(int *quote, char ch)
{
	*quote = (int)ch;
	return (1);
}

static int	is_env(int quote, char ch)
{
	if (ch == '$' && (quote != '\''))
		return (1);
	return (0);
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

static int	env_to_list(t_list **text_list, char *str, int *str_i, t_var_lst *env_lst)
{
	char	*env_str;
	t_list	*new;

	env_str = expand_env(str + *str_i + 1, str_i, env_lst);
	if (!env_str)
		return (0);
	new = ft_lstnew(env_str);
	if (!new)
	{
		free(env_str);
		return (0);
	}
	ft_lstadd_back(text_list, new);
	return (1);
}


int	get_text_list(t_list **text_list, char *buff, char *str, t_var_lst *env_lst)
{
	int	si;
	int	bi;
	int	quote;

	si = 0;
	bi = 0;
	quote = 0;
	while (str[si])
	{
		if (!quote && (str[si] == '\'' || str[si] == '\"') && \
			set_quote(&quote, str[si]) && !buff_to_list(buff, &bi, text_list))
			return (SYS);
		else if (quote == str[si] && set_quote(&quote, 0) && \
				!buff_to_list(buff, &bi, text_list))
			return (SYS);
		else if (is_env(quote, str[si]) && !buff_to_list(buff, &bi, text_list) \
				&& !env_to_list(text_list, str, &si, env_lst))
			return (SYS);
		else
			buff[bi++] = str[si];
		si++;
	}
	if (!buff_to_list(buff, &bi, text_list))
		return (SYS);
	return (NONE);
}