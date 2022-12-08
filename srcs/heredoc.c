#include "./parse.h"

char	*get_tmp_name(void)
{
	static int tmp_num;
	char	tmp_name[10] = "tmp";
	tmp_name[3] = tmp_num + '0';
	tmp_name[4] = '\0';
	tmp_num++;
	return (ft_strjoin("./", tmp_name));
}

// here_list -> tmp_list;
// here_list->content에 대해 replace_symbol을 하고 quote도 표시
t_list	*here_doc(t_cmd_info *cmd_arr, int pipe_num, t_list *here_list, t_var_lst *env_lst)
{
	char	*line;
	char	*delim;
	char	*tmp_file;
	int		tmp_fd;
	int		quote_flag;
	t_list	*tmp_list;
	t_list	*cur;


	tmp_list = NULL;
	cur = here_list;
	while (cur)
	{
		// replace quote
		delim = (cur->content);
		quote_flag = (ft_strchr(delim, '\'') || ft_strchr(delim, '\"'));
		tmp_file = get_tmp_name(); // malloc
		tmp_fd = open(tmp_file, O_WRONLY | O_CREAT, 00644);
		printf("--------------\n");
		printf(" [delim: %s], [tmp: %s]\n", delim, tmp_file);
		while (1)
		{
			line = readline(" mini_here> ");
			if (!ft_strncmp(line, delim, ft_strlen(delim) + 1))
				break;
			// replace env
			ft_putendl_fd(line, tmp_fd);
			free(line);
		}
		close(tmp_fd);
		ft_lstadd_back(&tmp_list, ft_lstnew(tmp_file));
		cur = cur->next;
	}
	return (tmp_list);
}
// void	pre_here_doc(t_cmd_info *cmd_arr, int pipe_num)
// {
// 	char	*line;
// 	char	*delim;
// 	char	*tmp_file;
// 	int		tmp_fd;
// 	int		cmd_i;
// 	int		redir_i;
// 	int		here_i;

// 	cmd_i = 0;
// 	while (cmd_i < pipe_num + 1)
// 	{
// 		redir_i = 0;
// 		here_i = 0;
// 		while (redir_i < cmd_arr[cmd_i].redir_num)
// 		{
// 			if (cmd_arr[cmd_i].redir[redir_i].type == HERE_DOC)
// 			{
// 				delim = cmd_arr[cmd_i].redir[redir_i].str;
// 				tmp_file = get_tmp_name(); // malloc
// 				tmp_fd = open(tmp_file, O_WRONLY | O_CREAT, 00644);
// 				while (1)
// 				{
// 					line = readline("here> ");
// 					if (!ft_strncmp(line, delim, ft_strlen(delim) + 1))
// 						break;
// 					ft_putstr_fd(line, tmp_fd);
// 					ft_putstr_fd("\n", tmp_fd);
// 					free(line);
// 				}
// 				cmd_arr[cmd_i].redir[redir_i].type = INFILE;
// 				cmd_arr[cmd_i].redir[redir_i].str = tmp_file;
// 				cmd_arr[cmd_i].here[here_i] = ft_strdup(tmp_file);
// 				free(delim);
// 				close(tmp_fd);
// 				here_i++;
// 			}
// 			redir_i++;
// 		}
// 		cmd_i++;
// 	}
// }