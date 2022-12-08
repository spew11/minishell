#include "./parse.h"

void	token_err(char *str, int *syntax_err)
{
	//free함수 만들기
	if (syntax_err)
		*syntax_err = 1;
	ft_putstr_fd("token syntax error : `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\'\n", 2);
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

void	init_cmd_info_val(t_cmd_info *cmd_info_arr, int pipe_num)
{
	int	i;

	i = 0;
	while (i < pipe_num + 1)
	{
		cmd_info_arr[i].argc = 0;
		cmd_info_arr[i].argv = NULL;
		cmd_info_arr[i].redir_num = 0;
		cmd_info_arr[i].redir = NULL;
		cmd_info_arr[i].here_num = 0;
		cmd_info_arr[i].here = NULL;
		i++;
	}
}

int	init_cmd_argv(t_cmd_info *cmd_info, int *cnt)
{
	int	i;

	i = 0;
	cmd_info->argc = cnt[ARGC];
	cmd_info->argv = malloc(sizeof(char *) * (cnt[ARGC] + 1));
	if (!cmd_info->argv)
		return (0);
	i = 0;
	while (i < cnt[ARGC] + 1)
	{
		cmd_info->argv[i] = NULL;
		i++;
	}
	ft_putstr_fd("argv_malloc: ", 2);
	ft_putnbr_fd(cnt[ARGC] + 1, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int	init_cmd_redir(t_cmd_info *cmd_info, int *cnt)
{
	int	i;

	i = 0;
	cmd_info->redir_num = cnt[REDIR];
	cmd_info->redir = malloc(sizeof(t_redir) * (cnt[REDIR] + 1));
	if (!cmd_info->redir)
		return (0);
	i = 0;
	while (i < cnt[REDIR] + 1)
	{
		cmd_info->redir[i].type = 0;
		cmd_info->redir[i].str = NULL;
		i++;
	}
	ft_putstr_fd("redir_malloc: ", 2);
	ft_putnbr_fd(cnt[REDIR] + 1, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int	init_cmd_here(t_cmd_info *cmd_info, int *cnt)
{
	int	i;

	i = 0;
	cmd_info->here_num = cnt[HERE];
	cmd_info->here = malloc(sizeof(char *) * (cnt[HERE] + 1));
	if (!cmd_info->here)
		return (0);
	i = 0;
	while (i < cnt[HERE] + 1)
	{
		cmd_info->here[i] = NULL;
		i++;
	}
	ft_putstr_fd("here_malloc: ", 2);
	ft_putnbr_fd(cnt[HERE] + 1, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int	init_cmd_info(t_cmd_info **cmd_info, int cmd_i, int *cnt)
{
	if (!init_cmd_argv((*cmd_info + cmd_i), cnt) || \
		!init_cmd_redir((*cmd_info + cmd_i), cnt) \
		|| !init_cmd_here((*cmd_info + cmd_i), cnt))
		return (0);
	printf("[argc: %d, redir: %d]\n", cnt[ARGC], cnt[REDIR]);
	cnt[ARGC] = 0;
	cnt[REDIR] = 0;
	cnt[HERE] = 0;
	return (1);
}
void	init_para(int *p_cmd_i, int *cnt)
{
	*p_cmd_i = 0;
	cnt[ARGC] = 0;
	cnt[REDIR] = 0;
	cnt[HERE] = 0;
}
int	pipe_err(int *cnt, char *token, char *err_str)
{
	if (!cnt[ARGC] && !cnt[REDIR])
	{
		err_str = token;
		return (0);
	}
	return (1);
}
int	is_pipe(char *token)
{
	if (!ft_strncmp(token, "|", 2))
		return (1);
	return (0);
}
int	is_here(char *token)
{
	if (!ft_strncmp(token, "<<", 3))
		return (1);
	return (0);
}
int	check_redir_err(char *token, char *err_str)
{
	if (is_redir(token) || is_pipe(token))
	{
		err_str = token;
		return (1);
	}
	return (0);
}
int	append_here_list(t_cmd_info **cmd_info_arr, t_list **here_list, char *token)
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
// stntax_err -> err_str설정 return (0)
// malloc_err -> return (0)
// success -> return (1)
int	malloc_cmd_info_arr(t_cmd_info **cmd_info_arr, t_list *cur, \
	t_list **here_list, char *err_str)
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
				!append_here_list(cmd_info_arr, here_list, cur->next->content)))
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
// malloc_err -> cmd_info = NULL
// syntax_err -> cmd_info != NULL
t_cmd_info	*init_cmd_info_arr(t_list *token_list, int pipe_num, \
			t_list **here_list, int *syntax_err)
{
	t_cmd_info	*cmd_info_arr;
	char		*err_str;

	cmd_info_arr = malloc(sizeof(t_cmd_info) * (pipe_num + 1)); // malloc
	if (!cmd_info_arr)
		return (NULL);
	init_cmd_info_val(cmd_info_arr, pipe_num);
	err_str = NULL; // not malloc
	if (!malloc_cmd_info_arr(&cmd_info_arr, token_list, here_list, err_str))
	{
		if (err_str)
			token_err(err_str, syntax_err);
		else
			cmd_info_free(&cmd_info_arr, pipe_num);
	}
	return (cmd_info_arr);// cmd_info_arr은 마지막에 null을 넣지않고 pipe_num으로 다뤄줘야한다.
}
