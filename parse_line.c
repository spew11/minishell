#include "w_minishell.h"

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


void	unclosed_quote_err(t_list *el_list)
{
	printf("unclosed quote err");
}
int is_space(char ch)
{
	if ((9 <= ch && 13 >= ch) || ch == 32)
		return (1);
	return (0);
}
// cat  <"ou "t 
t_list	*split_line(char *line, t_var_lst *env_lst)
{
	t_list	*spl_list;
	int		el_start_i;
	int		line_i;
	int		quote_flag;

	spl_list = NULL;
	el_start_i = 0;
	line_i = 0;
	quote_flag = 0; // NOT
	while (line[line_i])
	{
		if (!quote_flag && is_space(line[line_i])) {
			if (el_start_i != line_i)
				ft_lstadd_back(&spl_list, ft_lstnew(ft_substr(line, el_start_i, line_i - el_start_i)));
			el_start_i = line_i + 1;
		}
		else if (!quote_flag && (line[line_i] == '\"' || line[line_i] == '\''))
			quote_flag = line[line_i];
		else if (quote_flag == line[line_i])
			quote_flag = 0;
		line_i++;
	}
	// null로 끝난거 처리
	if (quote_flag)
		unclosed_quote_err(spl_list);
	if (el_start_i != line_i)
		ft_lstadd_back(&spl_list, ft_lstnew(ft_substr(line, el_start_i, line_i - el_start_i)));
	ft_lstiter(spl_list, print);printf("\n");
	return (spl_list);
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
	// buff가 flag이면서 일반문자를 받았을때
	if (is_flag(buff))
		return (1);
	// buff가 flag가 아니면서 일반문자를 받았을때
	return (0);
}
t_list *get_element_list(char *line, t_var_lst *env_lst)
{
	t_list	*el_list = NULL;
	t_list	*spl_list = NULL;
	t_list	*cur;
	char	*buff;
	int		con_i = 0;
	int		buf_i = 0;
	int		quote_flag = 0;

	spl_list = split_line(line, env_lst); // malloc
	cur = spl_list;
	while (cur) {
		buff = malloc(sizeof(char) * (ft_strlen(cur->content) + 1)); // malloc
		ft_bzero(buff, sizeof(char) * (ft_strlen(cur->content) + 1));
		con_i = 0;
		buf_i = 0;
		while (((char *)(cur->content))[con_i]) {
			if (ft_strncmp(buff, "", 1) && !quote_flag && is_new_element((char *)cur->content, con_i, buff)) {
				buff[buf_i] = '\0';
				ft_lstadd_back(&el_list, ft_lstnew(ft_strdup(buff)));
				// ft_lstiter(el_list, print);printf("\n");
				ft_bzero(buff, ft_strlen(buff));
				buf_i = 0;
			}
			if (!quote_flag && (((char *)(cur->content))[con_i] == '\'' || ((char *)(cur->content))[con_i] == '\"'))
				quote_flag = ((char *)(cur->content))[con_i];
			else if (quote_flag == ((char *)(cur->content))[con_i])
				quote_flag = 0;
			buff[buf_i] = ((char *)(cur->content))[con_i];
			buf_i++;
			con_i++;
		}
		buff[buf_i] = '\0';
		ft_lstadd_back(&el_list, ft_lstnew(ft_strdup(buff)));
		// ft_lstiter(el_list, print);printf("\n");
		free(buff);
		cur = cur->next;
	}
	return (el_list);
}

void	flag_err(char *str)
{
	//free함수 만들기
	printf("token syntax error : %s\n", str);
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
			printf("[argc: %d, redir: %d]\n", cnt[ARGC], cnt[REDIR]);
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
	printf("[argc: %d, redir: %d]\n", cnt[ARGC], cnt[REDIR]);
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
// $뒤에 특수기호가 오는 상황은 나중에 해야함
char	*expand_env(char *substr, int *str_i, t_var_lst *env_lst)
{
	t_var_lst	*cur;
	int			len;

	if (substr[0] == '?') {
		*str_i += 1;
		return (ft_strdup("exit status"));
	}
	len = 0;
	while (ft_isalpha(substr[len]) || ft_isalnum(substr[len]))
		len++;
	*str_i += len;
	cur = env_lst;
	while (cur)
	{
		if (!strncmp(substr , cur->var, len) && cur->var[len] == '\0')
			return (ft_strdup(cur->val));
		cur = cur->next;
	}
	return (ft_strdup(""));
}
char	*connect_list(t_list *list)
{
	char	*text;
	t_list	*cur;
	int		len;

	len = 0;
	cur = list;
	while (cur)
	{
		len += ft_strlen((char *)(cur->content));
		cur = cur->next;
	}
	text = malloc(sizeof(char) * (len + 1));
	ft_bzero(text, sizeof(char) * (len+1));
	cur = list;
	while (cur)
	{
		ft_strlcat(text, (char *)(cur->content), len + 1);
		cur = cur->next;
	}
	return (text);
}
char	*replace_symbol_to_text(char *str, t_var_lst *env_lst)
{
	t_list	*text_list = NULL;
	char	*text;
	char	*buff;
	int		str_i = 0;
	int		buf_i = 0;
	int		quote_flag = 0;

	buff = malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_bzero(buff, (ft_strlen(str) + 1));
	while (str[str_i])
	{
		if (!quote_flag && (str[str_i] == '\'' || str[str_i] == '\"')) {
			buff[buf_i] = '\0';
			ft_lstadd_back(&text_list, ft_lstnew(ft_strdup(buff)));
			ft_bzero(buff, (ft_strlen(str) + 1));
			buf_i = 0;
			quote_flag = str[str_i];
		}
		else if (quote_flag == str[str_i]) {
			buff[buf_i] = '\0';
			ft_lstadd_back(&text_list, ft_lstnew(ft_strdup(buff)));
			ft_bzero(buff, (ft_strlen(str) + 1));
			buf_i = 0;
			quote_flag = 0;
		}
		else if (str[str_i] == '$' && (quote_flag != '\'')) {
			buff[buf_i] = '\0';
			ft_lstadd_back(&text_list, ft_lstnew(ft_strdup(buff)));
			ft_bzero(buff, (ft_strlen(str) + 1));
			buf_i = 0;
			ft_lstadd_back(&text_list, ft_lstnew(expand_env(str + str_i + 1, &str_i, env_lst)));
		}
		else
			buff[buf_i++] = str[str_i];
		str_i++;
	}
	buff[buf_i] = '\0';
	ft_lstadd_back(&text_list, ft_lstnew(ft_strdup(buff)));
	text = connect_list(text_list);
	// clear함수 만들기
	return (text);
}

void	fill_cmd_info_arr(t_cmd_info *cmd_info_arr, t_list *el_list, t_var_lst *env_lst)
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
			cmd_info_arr[cmd_i].redir[re_i].str = replace_symbol_to_text(cur->content, env_lst);
			re_i += 1;
		}
		else {
			cmd_info_arr[cmd_i].argv[av_i] = replace_symbol_to_text(cur->content, env_lst);
			av_i += 1;
		}
		cur = cur -> next;
	}
}

t_cmd_info *get_cmd_info(t_list *el_list, int pipe_num, t_var_lst *env_lst)
{
	t_cmd_info	*cmd_info_arr;

	cmd_info_arr = init_cmd_info_arr(el_list, pipe_num);
	fill_cmd_info_arr(cmd_info_arr, el_list, env_lst);
	return (cmd_info_arr);
}

t_cmd_info	*parse_line(char *line, int *pipe_num, t_var_lst *env_lst)
{
	t_list		*el_list;
	t_cmd_info	*cmd_info_arr;

	// 역할에 구분없이 그냥 쪼개서 리스트에 담는다.
	// line -> el_list
	el_list = get_element_list(line, env_lst); // malloc
	ft_lstiter(el_list, print);printf("\n");
	
	// el_list -> cmd_info_arr
	*pipe_num = count_pipe(el_list);
	printf("[pipe_num: %d]\n", *pipe_num);//
	cmd_info_arr = get_cmd_info(el_list, *pipe_num, env_lst); // malloc
	print_cmd_arr(cmd_info_arr, *pipe_num);//
	return (cmd_info_arr);
}

/*

delim 'white_space', '<', '<<', '>', '>>', '|', '-'

*/
