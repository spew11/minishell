#include "./parse.h"

static int	ft_err(int err)
{
	if (err == SYS)
		return (SYS);
	ft_putstr_fd("token syntax error : `", 2);
	ft_putstr_fd("newline", 2);
	ft_putstr_fd("\'\n", 2);
	return (SYN);
}

static int	is_syn_err(t_list *cur_token, int *syntax_err)
{
	if (!cur_token->next)
	{
		*syntax_err = SYN;
		return (1);
	}
	return (0);
}

static int	init_idx(int *idx, int cmd)
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
		else if (!is_pipe(cur_token->content) && !is_redir(cur_token->content))
			cmd_info_arr[idx[CMD]].argv[idx[AV]++] \
			= replace_symbol_to_text(cur_token->content, env_lst, &err);
		if (err != NONE)
			return (ft_err(err));
		cur_token = cur_token->next;
	}
	return (NONE);
}
