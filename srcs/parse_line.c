#include "parse.h"

static int count_pipe(t_list *token_list)
{
	t_list	*cur;
	int		pipe_num;

	cur = token_list;
	pipe_num = 0;
	while (cur)
	{
		if (!ft_strncmp(cur->content, "|", 2))
			pipe_num += 1;
		cur = cur -> next;
	}
	return (pipe_num);
}

t_cmd_info	*parse_line(char *line, int *pipe_num, t_var_lst *env_lst)
{
	t_cmd_info	*cmd_info_arr;
	t_list		*token_list;
	t_list		*here_list;
	t_list		*tmp_list;
	int			syntax_err;

	token_list = divide_line_into_token(line); // malloc
	if (!token_list)
		return (NULL);
	ft_lstiter(token_list, print);printf("\n");
	
	*pipe_num = count_pipe(token_list);
	printf("[pipe_num: %d]\n", *pipe_num);

	here_list = NULL;
	syntax_err = 0;
	cmd_info_arr = init_cmd_info_arr(token_list, *pipe_num, &here_list, &syntax_err); // malloc
	if (!cmd_info_arr)
		return (NULL);//token_list free함수 만들기
	printf("here: ");ft_lstiter(here_list, print);printf("\n");

	tmp_list = here_doc(cmd_info_arr, *pipe_num, here_list, env_lst);
	printf("tmp: ");ft_lstiter(tmp_list, print);printf("\n");
	
	if (syntax_err)
	{
		printf("\nsyntax_err exit\n");
		// free함수
		return (NULL);
	}
	syntax_err = fill_cmd_info_arr(cmd_info_arr, token_list, tmp_list, env_lst); // malloc
	if (syntax_err) {
		printf("\nsyntax_err exit\n");
		// free함수
		return (NULL);
	}
	print_cmd_arr(cmd_info_arr, *pipe_num);
	return (cmd_info_arr);
}
