#include "./parse.h"
int exit_status;

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

	if (substr[0] == '?') {
		*str_i += 1;
		return (ft_strdup(ft_itoa(exit_status)));
	}
	len = 0;
	while (ft_isalpha(substr[len]) || ft_isalnum(substr[len]))
		len++;
	*str_i += len;
	cur = env_lst;
	while (cur)
	{
		if (!strncmp(substr , cur->var, len) && cur->var[len] == '\0')
			return (ft_strdup(cur->val));
		cur = cur->next;
	}
	return (ft_strdup(""));
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
	ft_bzero(text, sizeof(char) * (len + 1));
	cur = list;
	while (cur)
	{
		ft_strlcat(text, (char *)(cur->content), len + 1);
		cur = cur->next;
	}
	return (text);
}

char	*replace_symbol_to_text(char *str, t_var_lst *env_lst)
{
	t_list	*text_list;
	char	*text;
	char	*buff;
	int		str_i = 0;
	int		buf_i = 0;
	int		quote_flag = 0;

	
	buff = malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_bzero(buff, (ft_strlen(str) + 1));
	text_list = NULL;
	while (str[str_i])
	{
		if (!quote_flag && (str[str_i] == '\'' || str[str_i] == '\"'))
		{
			append_buff_to_list(buff, &buf_i, &text_list);
			quote_flag = str[str_i];
		}
		else if (quote_flag == str[str_i])
		{
			append_buff_to_list(buff, &buf_i, &text_list);
			quote_flag = 0;
		}
		else if (str[str_i] == '$' && (quote_flag != '\''))
		{
			append_buff_to_list(buff, &buf_i, &text_list);
			ft_lstadd_back(&text_list, ft_lstnew(expand_env(str + str_i + 1, &str_i, env_lst)));
		}
		else
			buff[buf_i++] = str[str_i];
		str_i++;
	}
	append_buff_to_list(buff, &buf_i, &text_list);
	text = connect_list(text_list);
	// clear함수 만들기
	return (text);
}

int	fill_cmd_info_arr(t_cmd_info *cmd_info_arr, t_list *token_list, t_list *tmp_list, t_var_lst *env_lst)
{
	t_list	*cur_token;
	t_list	*cur_tmp;
	int		cmd_i;
	int		av_i;
	int		re_i;
	int		here_i;

	cur_token = token_list;
	cur_tmp = tmp_list;
	av_i = 0;
	re_i = 0;
	cmd_i = 0;
	here_i = 0;
	// 파이프 마지막 전까지의 cmd_info
	while (cur_token)
	{
		if (!ft_strncmp(cur_token -> content, "|", 2))
		{
			if (!cur_token->next)
			{
				token_err("newline", NULL);
				return (1);
			}
			av_i = 0;
			re_i = 0;
			here_i = 0;
			cmd_i += 1;
		}
		else if (is_redir(cur_token -> content))
		{
			cmd_info_arr[cmd_i].redir[re_i].type = get_type(cur_token->content);
			if (cur_token->next)
			{
				cur_token = cur_token -> next;
				if (cmd_info_arr[cmd_i].redir[re_i].type == HERE_DOC)
				{
					cmd_info_arr[cmd_i].redir[re_i].type = INFILE;
					cmd_info_arr[cmd_i].redir[re_i].str = ft_strdup(cur_tmp->content);
					cmd_info_arr[cmd_i].here[here_i] = ft_strdup(cur_tmp->content);
					cur_tmp = cur_tmp->next;
					here_i += 1;
				}
				else
					cmd_info_arr[cmd_i].redir[re_i].str = replace_symbol_to_text(cur_token->content, env_lst);
				re_i += 1;
			}
			else
			{
				token_err("newline", NULL);
				return (1);
			}
		}
		else
		{
			cmd_info_arr[cmd_i].argv[av_i] = replace_symbol_to_text(cur_token->content, env_lst);
			av_i += 1;
		}
		cur_token = cur_token -> next;
	}
	return (0);
}
