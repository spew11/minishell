#include "parse.h"

void	cmd_info_free(t_cmd_info **cmd_info_arr, int pipe_num)
{
	int	i;

	i = 0;
	while (i < pipe_num + 1)
	{
		if ((*cmd_info_arr)[i].argv)
			free((*cmd_info_arr)[i].argv);
		if ((*cmd_info_arr)[i].redir)
			free((*cmd_info_arr)[i].redir);
		if ((*cmd_info_arr)[i].here)
			free((*cmd_info_arr)[i].here);
		i++;
	}
	free(*cmd_info_arr);
	*cmd_info_arr = NULL;
}
t_cmd_info	*sys_call_err(t_list **token_list, t_cmd_info **cmd_info_arr, \
			int pipe_num, t_list **tmp_list)
{
	perror("minishell");
	ft_lstclear(token_list, ft_free);
	if (cmd_info_arr)
		cmd_info_free(cmd_info_arr, pipe_num);
	if (tmp_list)
		ft_lstclear(tmp_list, ft_free);
	return (NULL);
}

t_cmd_info	*ft_syn_err(t_list **token_list, t_cmd_info **cmd_info_arr, \
			int pipe_num, t_list **tmp_list)
{
	ft_lstclear(token_list, ft_free);
	cmd_info_free(cmd_info_arr, pipe_num);
	ft_lstclear(tmp_list, ft_free);
	return (NULL);
}
t_cmd_info	*parse_line(char *line, int *pipe_num, t_var_lst *env_lst)
{
	// 아래 구조체 4개는 각자의 함수에서 만들어진 이후에는 parse_line함수에서만 free한다.
	// 구조체를 만들다가 실패 했을때만 해당 함수 안에서 만들던 것을 free하고 null을 return한다.
	t_cmd_info	*cmd_info_arr;
	t_list		*token_list;
	t_list		*here_list;
	t_list		*tmp_list;
	int			err;

	token_list = divide_line_into_token(line, pipe_num);
	if (!token_list)
		return (NULL);
	ft_lstiter(token_list, print);printf("\n");printf("[pipe_num: %d]\n", *pipe_num);
	cmd_info_arr = init_cmd_info_arr(token_list, *pipe_num, &here_list, &err);
	if (!cmd_info_arr)
		return (sys_call_err(&token_list, NULL, 0, NULL));
	printf("here: ");ft_lstiter(here_list, print);printf("\n");
	tmp_list = here_doc(cmd_info_arr, *pipe_num, here_list, &err);
	ft_lstclear(&here_list, ft_free);
	if (err == SYN)
		return (ft_syn_err(&token_list, &cmd_info_arr, *pipe_num, &tmp_list));
	if (err == SYS)
		return (sys_call_err(&token_list, &cmd_info_arr, *pipe_num, NULL));
	printf("tmp: ");ft_lstiter(tmp_list, print);printf("\n");
	err = fill_cmd_info_arr(cmd_info_arr, token_list, tmp_list, env_lst);
	if (err == SYN)
		return (ft_syn_err(&token_list, &cmd_info_arr, *pipe_num, &tmp_list));
	if (err == SYS)
		return (sys_call_err(&token_list, &cmd_info_arr, *pipe_num, &tmp_list));
	print_cmd_arr(cmd_info_arr, *pipe_num);
	return (cmd_info_arr);
}

// t_cmd_info	*parse_line(char *line, int *pipe_num, t_var_lst *env_lst)
// {
// 	t_cmd_info	*cmd_info_arr;
// 	t_list		*token_list;
// 	t_list		*here_list;
// 	t_list		*tmp_list;
// 	int			syntax_err;

// 	// malloc_err -> return (NULL)
// 	token_list = divide_line_into_token(line); // malloc
// 	if (!token_list)
// 		return (NULL);
// 	ft_lstiter(token_list, print);printf("\n");
	
// 	*pipe_num = count_pipe(token_list);
// 	printf("[pipe_num: %d]\n", *pipe_num);

// 	here_list = NULL;
// 	syntax_err = 0;
// 	// malloc_err -> return (NULL)
// 	cmd_info_arr = init_cmd_info_arr(token_list, *pipe_num, &here_list, &syntax_err); // malloc
// 	if (!cmd_info_arr)
// 	{
// 		ft_putendl_fd("malloc_err", 2);
// 		return (NULL);//token_list free함수 만들기
// 	}
// 	printf("here: ");ft_lstiter(here_list, print);printf("\n");

// 	tmp_list = here_doc(cmd_info_arr, *pipe_num, here_list);
// 	if (tmp_list)
// 	{
// 		ft_putendl_fd("malloc_err", 2);
// 		//free함수
// 		return (NULL);
// 	}
// 	printf("tmp: ");ft_lstiter(tmp_list, print);printf("\n");
	
// 	if (syntax_err)
// 	{
// 		printf("\nsyntax_err exit\n");
// 		// free함수
// 		return (NULL);
// 	}
// 	syntax_err = fill_cmd_info_arr(cmd_info_arr, token_list, tmp_list, env_lst); // malloc
// 	if (syntax_err) {
// 		printf("\nsyntax_err exit\n");
// 		// free함수
// 		return (NULL);
// 	}
// 	print_cmd_arr(cmd_info_arr, *pipe_num);
// 	return (cmd_info_arr);
// }
