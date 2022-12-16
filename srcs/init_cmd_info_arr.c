#include "./parse.h"

static void	token_err(char *str, int *syntax_err)
{
	if (syntax_err)
		*syntax_err = SYN;
	ft_putstr_fd("token syntax error : `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\'\n", 2);
}

static void	init_cmd_info_val(t_cmd_info *cmd_info_arr, int pipe_num)
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
// malloc_err -> cmd_info == NULL
// syntax_err -> cmd_info && syntax_err == 1
// success -> cmd_info && syntax_err == 0
// do not free token_list
t_cmd_info	*init_cmd_info_arr(t_list *token_list, int pipe_num, \
			t_list **here_list, int *syntax_err)
{
	t_cmd_info	*cmd_info_arr;
	char		*err_str;

	*here_list = NULL;
	*syntax_err = NONE;
	cmd_info_arr = malloc(sizeof(t_cmd_info) * (pipe_num + 1));
	if (!cmd_info_arr)
		return (NULL);
	init_cmd_info_val(cmd_info_arr, pipe_num);
	err_str = NULL;
	if (!malloc_cmd_info_arr(&cmd_info_arr, token_list, here_list, &err_str))
	{
		if (err_str)
			token_err(err_str, syntax_err);
		else
			cmd_info_free(&cmd_info_arr, pipe_num);
	}
	return (cmd_info_arr);
}
