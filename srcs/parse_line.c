#include "minishell.h"

#define ARGV	11
#define	OPT		12
#define PIPE	13

char *convert_envp();

int	is_flag(char *str)
{
	if (!ft_strncmp(str, "<", 2))
		return (1);
	if (!ft_strncmp(str, "<<", 3))
		return (1);
	if (!ft_strncmp(str, ">", 2))
		return (1);
	if (!ft_strncmp(str, ">>", 3))
		return (1);
	if (!ft_strncmp(str, "|", 2))
		return (1);
	return (0);
}

int	is_new_element(char *str, int jdx, char *buff)
{
	// flag를 버퍼에 넣는 상황
	if (str[jdx] == '|')
		return (1);
	else if (str[jdx] == '<') {
		if (!ft_strncmp(buff, "<", 2))
			return (0);
		return (1);
	}
	else if (str[jdx] == '>') {
		if (!ft_strncmp(buff, ">", 2))
			return (0);
		return (1);
	}
	// flag가 아닌 일반 문자일때 buff가 flag이면 새로 담아야한다.
	if (is_flag(buff))
		return (1);
	return (0);
}

t_list *get_element_list(char *line, char *envp[])
{
	t_list	*el_list = NULL;
	char	**spl;
	char	*buff;
	int 	spl_i = 0;
	int		spl_j = 0;
	int		buf_i = 0;

	spl = ft_split(line, ' '); // malloc
	while (spl[spl_i]) {
		buff = malloc(sizeof(char) * (ft_strlen(spl[spl_i]) + 1)); // malloc
		ft_bzero(buff, sizeof(char) * (ft_strlen(spl[spl_i]) + 1));
		spl_j = 0;
		buf_i = 0;
		while (spl[spl_i][spl_j]) {
			if (ft_strncmp(buff, "", 1) && is_new_element(spl[spl_i], spl_j, buff)) {
				buff[buf_i] = '\0';
				ft_lstadd_back(&el_list, ft_lstnew(ft_strdup(buff)));
				// ft_lstiter(el_list, print);printf("\n");
				ft_bzero(buff, ft_strlen(buff));
				buf_i = 0;
			}
			buff[buf_i] = spl[spl_i][spl_j];
			buf_i++;
			spl_j++;
		}
		buff[buf_i] = '\0';
		ft_lstadd_back(&el_list, ft_lstnew(ft_strdup(buff)));
		// ft_lstiter(el_list, print);printf("\n");
		free(buff);
		spl_i++;
	}
	return (el_list);
}

void	flag_err(char *str)
{
	//free함수 만들기
	printf("custom syntax error : %s\n", str);
}

int count_pipe(t_list *el_list)
{
	t_list	*cur;
	int		pipe_num;

	cur = el_list;
	pipe_num = 0;
	while (cur)
	{
		if (!ft_strncmp(cur->content, "|", 2))
			pipe_num += 1;
		cur = cur -> next;
	}
	return (pipe_num);
}

int	init_cmd_info(t_cmd_info *p_cmd_info, int argc, int redir_num)
{
	int	i;

	p_cmd_info->argc = argc;
	p_cmd_info->redir_num = redir_num;
	p_cmd_info->argv = malloc(sizeof(char *) * (argc + 1));
	i = 0;
	while (i < argc + 1)
	{
		p_cmd_info->argv[i] = NULL;
		i++;
	}
	p_cmd_info->redir = malloc(sizeof(t_redir) * (redir_num + 1));
	i = 0;
	while (i < redir_num + 1)
	{
		p_cmd_info->redir[i].type = 0;
		p_cmd_info->redir[i].str = NULL;
		i++;
	}
	// malloc err 체크
	return (1);
}

t_cmd_info	*init_cmd_info_arr(t_list *el_list, int pipe_num)
{
	t_cmd_info	*cmd_info_arr;
	t_list		*cur;
	int			cmd_i;
	int			cnt[2];

	cmd_info_arr = malloc(sizeof(t_cmd_info) * (pipe_num + 1)); //malloc
	cnt[ARGC] = 0;
	cnt[REDIR] = 0;
	cur = el_list;
	cmd_i = 0;
	// 파이프 마지막 전까지의 cmd_info를 malloc
	while (cur) {
		if (!ft_strncmp(cur -> content, "|", 2)) {
			init_cmd_info(cmd_info_arr + cmd_i, cnt[ARGC], cnt[REDIR]); // malloc ...err체크해야함?
			//printf("[argc: %d, redir: %d]\n", cnt[ARGC], cnt[REDIR]);
			if (!ft_strncmp(cur->next->content, "|", 2))
				flag_err(cur->next->content);
			cnt[ARGC] = 0;
			cnt[REDIR] = 0;
			cmd_i++;
		}
		else if (is_flag(cur -> content)) {
			cnt[REDIR] += 1;
			cur = cur -> next;
			if (is_flag(cur -> content))
				flag_err(cur -> content);
		}
		else
			cnt[ARGC] += 1;
		cur = cur -> next;
	}
	// 파이프의 마지막 or 파이프가 없는 상항 malloc
	init_cmd_info(cmd_info_arr + cmd_i, cnt[ARGC], cnt[REDIR]); // malloc
	//printf("[argc: %d, redir: %d]\n", cnt[ARGC], cnt[REDIR]);
	// cmd_info_arr은 마지막에 null을 넣지않고 pipe_num으로 다뤄줘야한다.
	return (cmd_info_arr);
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

void	fill_cmd_info_arr(t_cmd_info *cmd_info_arr, t_list *el_list)
{
	t_list	*cur;
	int		cmd_i;
	int		av_i;
	int		re_i;

	cur = el_list;
	av_i = 0;
	re_i = 0;
	cmd_i = 0;
	// 파이프 마지막 전까지의 cmd_info
	while (cur) {
		if (!ft_strncmp(cur -> content, "|", 2)) {
			av_i = 0;
			re_i = 0;
			cmd_i++;
		}
		else if (is_flag(cur -> content)) {
			cmd_info_arr[cmd_i].redir[re_i].type = get_type(cur->content);
			cur = cur -> next;
			cmd_info_arr[cmd_i].redir[re_i].str = ft_strdup(cur->content);
			re_i += 1;
		}
		else {
			cmd_info_arr[cmd_i].argv[av_i] = strdup(cur->content);
			av_i += 1;
		}
		cur = cur -> next;
	}
}

t_cmd_info *get_cmd_info(t_list *el_list, int pipe_num)
{
	t_cmd_info	*cmd_info_arr;

	cmd_info_arr = init_cmd_info_arr(el_list, pipe_num);
	fill_cmd_info_arr(cmd_info_arr, el_list);
	return (cmd_info_arr);
}

t_cmd_info	*parse_line(char *line, int *pipe_num, char *envp[])
{
	t_list		*el_list;
	t_cmd_info	*cmd_info_arr;

	// 역할에 구분없이 그냥 쪼개서 리스트에 담는다.
	// line -> el_list
	el_list = get_element_list(line, envp); //ft_lstiter(el_list, print);printf("\n"); //malloc
	
	// el_list -> cmd_info_arr
	*pipe_num = count_pipe(el_list);
	printf("[pipe_num: %d]\n", *pipe_num);//
	cmd_info_arr = get_cmd_info(el_list, *pipe_num); // malloc
	print_cmd_arr(cmd_info_arr, *pipe_num);//
	return (cmd_info_arr);
}

/*

delim 'white_space', '<', '<<', '>', '>>', '|', '-'

*/
