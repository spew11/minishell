#include "./parse.h"
int	g_exit_status;

int	get_type(char *str)
{
	if (!ft_strncmp(str, "<", 2))
		return (INFILE);
	if (!ft_strncmp(str, "<<", 3))
		return (HERE_DOC);
	if (!ft_strncmp(str, ">", 2))
		return (OUTFILE);
	if (!ft_strncmp(str, ">>", 3))
		return (FILE_APPEND);
	return (0);
}
// $뒤에 특수기호가 오는 상황은 나중에 해야함
char	*expand_env(char *substr, int *str_i, t_var_lst *env_lst)
{
	t_var_lst	*cur;
	int			len;

	if (substr[0] == '?')
	{
		*str_i += 1;
		return (ft_itoa(g_exit_status));
	}
	len = 0;
	while (ft_isalpha(substr[len]) || ft_isalnum(substr[len])) // 여기 환경변수 조건 수정 해야됨
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

int	set_quote(int *quote, char ch)
{
	*quote = (int)ch;
	return (1);
}
int	is_env(int quote, char ch)
{
	if (ch == '$' && (quote != '\''))
		return (1);
	return (0);
}

int	env_to_list(t_list **text_list, char *str, int *str_i, t_var_lst *env_lst)
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
char	*connect_list(t_list *list)
{
	char	*text;
	t_list	*cur;
	int		len;

	len = 0;
	cur = list;
	while (cur)
	{
		len += ft_strlen((char *)(cur->content));
		cur = cur->next;
	}
	text = malloc(sizeof(char) * (len + 1));
	if (!text)
		return (NULL);
	ft_bzero(text, sizeof(char) * (len + 1));
	cur = list;
	while (cur)
	{
		ft_strlcat(text, (char *)(cur->content), len + 1);
		cur = cur->next;
	}
	return (text);
}
char	*replace_symbol_to_text(char *str, t_var_lst *env_lst, int *err)
{
	t_list	*text_list;
	char	*text;
	char	*buff;

	buff = malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_bzero(buff, (ft_strlen(str) + 1));
	text_list = NULL;
	*err = get_text_list(&text_list, buff, str, env_lst);
	if (*err != NONE)
	{
		ft_lstclear(&text_list, ft_free);
		return (NULL);
	}
	text = connect_list(text_list);
	ft_lstclear(&text_list, ft_free);
	return (text);
}
int	is_syn_err(t_list *cur_token, int *syntax_err)
{
	if (!cur_token->next)
	{
		*syntax_err = SYN;
		return (1);
	}
	return (0);
}
int	init_idx(int *idx, int cmd)
{
	idx[AV] = 0;
	idx[RE] = 0;
	idx[HERE] = 0;
	if (cmd == 0)
		idx[CMD] = 0;
	else
		idx[CMD] += 1;
	return (0);
}

int	get_redir(t_cmd_info *cmd_info_arr, t_list *cur_token, \
	int *idx, t_var_lst *env_lst)
{
	int	err;

	err = NONE;
	cmd_info_arr[idx[CMD]].redir[idx[RE]].type = get_type(cur_token->content);
	cur_token = cur_token->next;
	cmd_info_arr[idx[CMD]].redir[idx[RE]].str \
	= replace_symbol_to_text(cur_token->content, env_lst, &err);
	idx[RE] += 1;
	return (err);
}

int	get_here_doc(t_cmd_info *cmd_info_arr, t_list *cur_token, \
	int *idx, t_list **cur_tmp)
{
	char	*tmp_file;

	cmd_info_arr[idx[CMD]].redir[idx[RE]].type = get_type(cur_token->content);
	cmd_info_arr[idx[CMD]].redir[idx[RE]].type = INFILE;
	tmp_file = ft_strdup((*cur_tmp)->content);
	if (!tmp_file)
		return (SYS);
	cmd_info_arr[idx[CMD]].redir[idx[RE]].str = tmp_file;
	tmp_file = ft_strdup((*cur_tmp)->content);
	if (!tmp_file)
		return (SYS);
	cmd_info_arr[idx[CMD]].here[idx[HERE]] = tmp_file;
	(*cur_tmp) = (*cur_tmp)->next;
	idx[HERE] += 1;
	idx[RE] += 1;
	return (NONE);
}

int	ft_err(int err)
{
	if (err == SYS)
		return (SYS);
	ft_putstr_fd("token syntax error : `", 2);
	ft_putstr_fd("newline", 2);
	ft_putstr_fd("\'\n", 2);
	return (SYN);
}
// malloc_err -> -1
// syntax_err -> 1
// success -> 0
int	fill_cmd_info_arr(t_cmd_info *cmd_info_arr, t_list *cur_token, \
	t_list *cur_tmp, t_var_lst *env_lst)
{
	int	idx[4];
	int	err;

	init_idx(idx, 0);
	err = NONE;
	while (cur_token)
	{
		if (is_pipe(cur_token->content) && !is_syn_err(cur_token, &err))
			init_idx(idx, 1);
		else if (is_redir(cur_token -> content) && !is_syn_err(cur_token, &err))
		{
			if (get_type(cur_token->content) == HERE_DOC)
				err = get_here_doc(cmd_info_arr, cur_token, idx, &cur_tmp);
			else
				err = get_redir(cmd_info_arr, cur_token, idx, env_lst);
			cur_token = cur_token->next;
		}
		else
			cmd_info_arr[idx[CMD]].argv[idx[AV]++] \
			= replace_symbol_to_text(cur_token->content, env_lst, &err);
		if (err != NONE)
			return (ft_err(err));
		cur_token = cur_token -> next;
	}
	return (NONE);
}
