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
	t_list		*token_list;
	t_list		*here_list;
	t_list		*tmp_list;
	t_cmd_info	*cmd_info_arr;
	int			syntax_err;

	// 가장 작은 token단위로 쪼개기(quote(X), envp(X))
	token_list = divide_line_into_token(line); // malloc
	ft_lstiter(token_list, print);printf("\n");
	
	*pipe_num = count_pipe(token_list);
	printf("[pipe_num: %d]\n", *pipe_num);

	// token 분류하기
	here_list = NULL;
	syntax_err = 0;
	cmd_info_arr = init_cmd_info_arr(token_list, *pipe_num, &here_list, &syntax_err); // malloc
	printf("here: ");
	ft_lstiter(here_list, print);printf("\n");
	tmp_list = here_doc(cmd_info_arr, *pipe_num, here_list, env_lst);
	printf("tmp: ");
	ft_lstiter(tmp_list, print);printf("\n");
	// syntax err check
	if (syntax_err) {
		printf("\nsyntax_err exit\n");
		return (NULL);
	}
	syntax_err = fill_cmd_info_arr(cmd_info_arr, token_list, tmp_list, env_lst); // malloc
	if (syntax_err) {
		printf("\nsyntax_err exit\n");
		return (NULL);
	}
	print_cmd_arr(cmd_info_arr, *pipe_num);
	return (cmd_info_arr);
}
