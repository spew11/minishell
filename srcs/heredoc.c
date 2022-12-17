#include "./parse.h"

void	tmp_clear(t_list **tmp_list)
{
	t_list	*cur;

	cur = *tmp_list;
	while (cur)
	{
		unlink(cur->content);
		cur = cur->next;
	}
	ft_lstclear(tmp_list, ft_free);
	*tmp_list = NULL;
}

static char	*get_tmp_name(void)
{
	static int	tmp_num;
	char		tmp_name[10] = "tmp";

	tmp_name[3] = tmp_num + '0';
	tmp_name[4] = '\0';
	tmp_num++;
	return (ft_strjoin("./", tmp_name));
}

static int	append_str_to_list(t_list **list, char *str)
{
	t_list	*new;

	new = ft_lstnew(str);
	if (!new)
		return (0);
	ft_lstadd_back(list, new);
	return (1);
}

// success -> return file_name;
// fail -> return NULL;
static char	*read_until_delim(char *delim)
{
	char	*line;
	char	*tmp_file;
	int		tmp_fd;

	tmp_file = get_tmp_name();
	if (!tmp_file)
		return (NULL);
	tmp_fd = open(tmp_file, O_WRONLY | O_CREAT, 00644);
	if (tmp_fd < 0)
	{
		free(tmp_file);
		return (NULL);
	}
	while (1)
	{
		line = readline("mini_here> ");
		if (!line || !ft_strncmp(line, delim, ft_strlen(delim) + 1))
			break ;
		ft_putendl_fd(line, tmp_fd);
		free(line);
	}
	close(tmp_fd);
	return (tmp_file);
}

// malloc_err, system_call_err -> NULL
// success -> tmp_list
t_list	*here_doc(t_cmd_info *cmd_arr, int pipe_num, t_list *here_list, int *err)
{
	char	*delim;	
	char	*tmp_file;
	t_list	*tmp_list;
	t_list	*cur_here;

	tmp_list = NULL;
	cur_here = here_list;
	while (cur_here && err != NONE)
	{
		delim = cur_here->content;
		tmp_file = read_until_delim(delim);
		if (!tmp_file)
		{
			tmp_clear(&tmp_list);
			*err = SYS;
		}
		if (!append_str_to_list(&tmp_list, tmp_file))
		{
			free(tmp_file);
			tmp_clear(&tmp_list);
			*err = SYS;
		}
		cur_here = cur_here->next;
	}
	return (tmp_list);
}
