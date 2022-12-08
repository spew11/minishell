#include "./parse.h"

void	ft_free(void *ptr)
{
	free(ptr);
}

int	is_new_token(char *str, int jdx, char *buff)
{
	if (str[jdx] == '|')
		return (1);
	else if (str[jdx] == '<')
	{
		if (!ft_strncmp(buff, "<", 2))
			return (0);
		return (1);
	}
	else if (str[jdx] == '>')
	{
		if (!ft_strncmp(buff, ">", 2))
			return (0);
		return (1);
	}
	if (is_redir(buff) || !ft_strncmp(buff, "|", 2))
		return (1);
	return (0);
}

void	unclosed_quote_err(t_list **token_list)
{
	ft_putendl_fd("unclosed quote err", 2);
	ft_lstclear(token_list, ft_free);
	*token_list = NULL;
}

int	is_space(char ch)
{
	if ((9 <= ch && 13 >= ch) || ch == 32)
		return (1);
	return (0);
}

static void	init_para(t_list **p_lst, int *num1, int *num2, int *num3)
{
	if (p_lst)
		*p_lst = NULL;
	if (num1)
		*num1 = 0;
	if (num2)
		*num2 = 0;
	if (num3)
		*num3 = 0;
}
// malloc null 가드
t_list	*split_by_space(char *line)
{
	t_list	*spl_list;
	int		start_i;
	int		line_i;
	int		quote_flag;

	init_para(&spl_list, &start_i, &line_i, &quote_flag);
	while (line[line_i])
	{
		if (!quote_flag && is_space(line[line_i]))
		{
			if (start_i != line_i)
				ft_lstadd_back(&spl_list, ft_lstnew(ft_substr(line, start_i, line_i - start_i))); // null가드
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
		unclosed_quote_err(&spl_list);
	else if (start_i != line_i)
		ft_lstadd_back(&spl_list, ft_lstnew(ft_substr(line, start_i, line_i - start_i)));// null가드
	ft_lstiter(spl_list, print);printf("\n");
	return (spl_list);
}

int	append_buff_to_list(char *buff, int *buf_i, t_list **token_list)
{
	char	*str;
	t_list	*new;

	buff[*buf_i] = '\0';
	str = ft_strdup(buff);
	if (!str)
	{
		ft_lstclear(token_list, ft_free);
		free(buff);
		return (0);
	}
	new = ft_lstnew(str);
	if (!new)
	{
		ft_lstclear(token_list, ft_free);
		free(str);
		free(buff);
		return (0);
	}
	ft_lstadd_back(token_list, new);
	ft_bzero(buff, ft_strlen(buff) + 1);
	*buf_i = 0;
	return (1);
}

int	get_token_from_spl(t_list **token_list, char *str)
{
	char	*buff;
	int		str_i;
	int		buf_i;
	int		quote_flag;

	buff = malloc(sizeof(char) * (ft_strlen(str) + 1)); // malloc
	if (!buff)
		return (0);
	init_para(NULL, &str_i, &buf_i, &quote_flag);
	while (str[str_i])
	{
		if (buf_i && !quote_flag && is_new_token(str, str_i, buff) \
			&& !append_buff_to_list(buff, &buf_i, token_list))
			return (0);
		if (!quote_flag && (str[str_i] == '\'' || str[str_i] == '\"'))
			quote_flag = str[str_i];
		else if (quote_flag == str[str_i])
			quote_flag = 0;
		buff[buf_i++] = str[str_i++];
	}
	if (!append_buff_to_list(buff, &buf_i, token_list))
		return (0);
	free(buff);
	return (1);
}

t_list	*divide_line_into_token(char *line)
{
	t_list	*token_list;
	t_list	*spl_list;
	t_list	*spl_cur;

	spl_list = split_by_space(line); // malloc
	if (!spl_list)
		return (NULL);
	token_list = NULL;
	spl_cur = spl_list;
	while (spl_cur)
	{
		if (!get_token_from_spl(&token_list, (char *)(spl_cur->content)))
		{
			ft_lstclear(&spl_list, ft_free);
			return (NULL);
		}
		spl_cur = spl_cur->next;
	}
	ft_lstclear(&spl_list, ft_free);
	return (token_list);
}
