#include "./parse.h"

void	token_err(char *str)
{
	//free함수 만들기
	printf("token syntax error : %s\n", str);
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

int	init_cmd_info(t_cmd_info *cmd_info, int *cnt)
{
	int	i;

	cmd_info->argc = cnt[ARGC];
	cmd_info->argv = malloc(sizeof(char *) * (cnt[ARGC] + 1));
	i = 0;
	while (i < cnt[ARGC] + 1)
	{
		cmd_info->argv[i] = NULL;
		i++;
	}
	cmd_info->redir_num = cnt[REDIR];
	cmd_info->redir = malloc(sizeof(t_redir) * (cnt[REDIR] + 1));
	i = 0;
	while (i < cnt[REDIR] + 1)
	{
		cmd_info->redir[i].type = 0;
		cmd_info->redir[i].str = NULL;
		i++;
	}
	cmd_info->here_num = cnt[HERE];
	cmd_info->here = malloc(sizeof(char *) * (cnt[HERE] + 1));
	i = 0;
	while (i < cnt[HERE] + 1)
	{
		cmd_info->here[i] = NULL;
		i++;
	}
	// malloc err 체크
	return (1);
}

t_cmd_info	*init_cmd_info_arr(t_list *token_list, int pipe_num, t_list **here_list)
{
	t_cmd_info	*cmd_info_arr;
	t_list		*cur;
	int			cmd_i;
	int			cnt[3];

	cmd_info_arr = malloc(sizeof(t_cmd_info) * (pipe_num + 1)); //malloc
	init_cmd_info_val(cmd_info_arr, pipe_num);
	cnt[ARGC] = 0;
	cnt[REDIR] = 0;
	cnt[HERE] = 0;
	cur = token_list;
	cmd_i = 0;
	// 파이프 마지막 전까지의 cmd_info를 malloc
	while (cur) {
		if (!ft_strncmp(cur -> content, "|", 2)) {
			if (cur->next && !ft_strncmp(cur->next->content, "|", 2))
			{
				token_err(cur->next->content);
				break;
			}
			init_cmd_info(cmd_info_arr + cmd_i, cnt);
			printf("[argc: %d, redir: %d]\n", cnt[ARGC], cnt[REDIR]);
			cnt[ARGC] = 0;
			cnt[REDIR] = 0;
			cnt[HERE] = 0;
			cmd_i++;
		}
		else if (is_redir(cur -> content)) {
			if (cur->next && (is_redir(cur->next->content) || !ft_strncmp(cur->next->content, "|", 2)))
			{
				token_err(cur->next->content);
				break;
			}
			cnt[REDIR] += 1;
			if (!ft_strncmp(cur -> content, "<<", 3) && cur->next) {
				cnt[HERE] += 1;
				ft_lstadd_back(here_list, ft_lstnew(strdup(cur->next->content)));
			}
			if (cur->next)
				cur = cur -> next;
		}
		else
			cnt[ARGC] += 1;
		cur = cur -> next;
	}
	// 파이프의 마지막 or 파이프가 없는 상항 malloc
	init_cmd_info(cmd_info_arr + cmd_i, cnt);
	printf("[argc: %d, redir: %d]\n", cnt[ARGC], cnt[REDIR]);
	// cmd_info_arr은 마지막에 null을 넣지않고 pipe_num으로 다뤄줘야한다.
	return (cmd_info_arr);
}