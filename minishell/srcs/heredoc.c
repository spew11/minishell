/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:36:38 by root              #+#    #+#             */
/*   Updated: 2022/12/18 17:44:30 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char		*tmp_num_str;
	char		*tmp_name;

	tmp_num_str = ft_itoa(tmp_num);
	if (!tmp_num_str)
		return (NULL);
	tmp_num += 1;
	tmp_name = ft_strjoin("/tmp/mini_tmp", tmp_num_str);
	free(tmp_num_str);
	return (tmp_name);
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
	line = NULL;
	while (g_exit_status != (-5))
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, delim, ft_strlen(delim) + 1))
			break ;
		ft_putendl_fd(line, tmp_fd);
		free(line);
	}
	free(line);
	close(tmp_fd);
	return (tmp_file);
}

// malloc_err, system_call_err -> NULL
// success -> tmp_list
t_list	*here_doc(t_list *here_list, int *err)
{
	char	*delim;	
	char	*tmp_file;
	t_list	*tmp_list;
	t_list	*cur_here;
	int		stdin_fd;

	tmp_list = NULL;
	cur_here = here_list;
	signal(SIGINT, sig_handler2);
	stdin_fd = dup(0);
	while (cur_here && err != NONE)
	{
		delim = cur_here->content;
		tmp_file = read_until_delim(delim);
		if (!tmp_file)
			tmp_err1(&tmp_list, err);
		if (!append_str_to_list(&tmp_list, tmp_file))
			tmp_err2(tmp_file, &tmp_list, err);
		cur_here = cur_here->next;
	}
	signal(SIGINT, sig_handler);
	dup2(stdin_fd, 0);
	close(stdin_fd);
	return (tmp_list);
}
