#include "./parse.h"

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