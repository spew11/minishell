#include "./parse.h"

int	is_new_token(char *str, int jdx, char *buff)
{
	// flag를 버퍼에 새로 넣는 상황
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
	if (is_redir(buff) || !ft_strncmp(buff, "|", 2))
		return (1);
	// buff가 flag가 아니면서 일반문자를 받았을때
	return (0);
}

void	unclosed_quote_err(t_list *token_list)
{
	printf("unclosed quote err");
}

int is_space(char ch)
{
	if ((9 <= ch && 13 >= ch) || ch == 32)
		return (1);
	return (0);
}

t_list	*split_by_space(char *line)
{
	t_list	*spl_list;
	int		start_i;
	int		line_i;
	int		quote_flag;

	spl_list = NULL;
	start_i = 0;
	line_i = 0;
	quote_flag = 0; // NOT
	while (line[line_i])
	{
		if (!quote_flag && is_space(line[line_i])) 
		{
			if (start_i != line_i)
				ft_lstadd_back(&spl_list, ft_lstnew(ft_substr(line, start_i, line_i - start_i)));
			start_i = line_i + 1;
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
	if (start_i != line_i)
		ft_lstadd_back(&spl_list, ft_lstnew(ft_substr(line, start_i, line_i - start_i)));
	ft_lstiter(spl_list, print);printf("\n");
	return (spl_list);
}

void	append_buff_to_list(char *buff, int *buf_i, t_list **token_list)
{
	buff[*buf_i] = '\0';
	ft_lstadd_back(token_list, ft_lstnew(ft_strdup(buff)));
	ft_bzero(buff, ft_strlen(buff) + 1);
	*buf_i = 0;
}

void	get_token_from_str(t_list **token_list, char *str)
{
	char	*buff;
	int		str_i = 0;
	int		buf_i = 0;
	int		quote_flag = 0;

	buff = malloc(sizeof(char) * (ft_strlen(str) + 1)); // malloc
	ft_bzero(buff, sizeof(char) * (ft_strlen(str) + 1));
	str_i = 0;
	buf_i = 0;
	while (str[str_i])
	{
		if (buf_i && !quote_flag && is_new_token(str, str_i, buff))
			append_buff_to_list(buff, &buf_i, token_list);
		if (!quote_flag && (str[str_i] == '\'' || str[str_i] == '\"'))
			quote_flag = str[str_i];
		else if (quote_flag == str[str_i])
			quote_flag = 0;
		buff[buf_i] = str[str_i];
		buf_i++;
		str_i++;
	}
	append_buff_to_list(buff, &buf_i, token_list);
	free(buff);
}

t_list *divide_line_into_token(char *line)
{
	t_list	*token_list = NULL;
	t_list	*spl_list = NULL;
	t_list	*spl_cur;
	

	// cat <infile |cat -e>"out file" -> [ cat ] [ <infile ] [ |cat ] [ -e>"out file" ]
	spl_list = split_by_space(line); // malloc
	spl_cur = spl_list;
	while (spl_cur) {
		// [ -e>"out file" ] -> [ -e ] [ > ] [ "out file" ]
		get_token_from_str(&token_list, (char *)(spl_cur->content));
		spl_cur = spl_cur->next;
	}
	//spl_list free
	return (token_list);
}