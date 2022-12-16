#include "./parse.h"

static char	*connect_list(t_list *list, int *err)
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
	if (!text)
	{
		*err = SYS;
		return (NULL);
	}
	ft_bzero(text, sizeof(char) * (len + 1));
	cur = list;
	while (cur)
	{
		ft_strlcat(text, (char *)(cur->content), len + 1);
		cur = cur->next;
	}
	return (text);
}

char	*replace_symbol_to_text(char *str, t_var_lst *env_lst, int *err)
{
	t_list	*text_list;
	char	*text;
	char	*buff;

	buff = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!buff)
	{
		*err = SYS;
		return (NULL);
	}
	ft_bzero(buff, (ft_strlen(str) + 1));
	text_list = NULL;
	*err = get_text_list(&text_list, buff, str, env_lst);
	if (*err != NONE)
	{
		ft_lstclear(&text_list, ft_free);
		return (NULL);
	}
	text = connect_list(text_list, err);
	ft_lstclear(&text_list, ft_free);
	return (text);
}
