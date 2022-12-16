/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:06:59 by eunjilee          #+#    #+#             */
/*   Updated: 2022/12/16 16:32:37 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pid_err(void)
{
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}

int	ft_access(const char *pathname)
{
	struct stat	statbuf;

	if (stat(pathname, &statbuf) == 0)
		return (0);
	return (-1);
}

static void	get_pathname_in_env(char *envp[], char *filename, char **pathname)
{
	char	*paths;
	char	**path;
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (envp[++i])
	{
		paths = ft_strchr(envp[i], '=') + 1;
		path = ft_split(paths, ':');
		j = -1;
		while (path[++j])
		{
			tmp = ft_strjoin(path[j], "/");
			if (*pathname)
				free(*pathname);
			*pathname = ft_strjoin(tmp, filename);
			free(tmp);
			if (ft_access(*pathname) == 0)
				return ;
		}
	}
	free(*pathname);
	*pathname = 0;
}

static char	*get_pathname(char *envp[], char *filename)
{
	char	*pathname;

	pathname = 0;
	if (envp == 0)
		return (0);
	if (ft_access(filename) == 0)
		return (filename);
	get_pathname_in_env(envp, filename, &pathname);
	return (pathname);
}

int	ft_execve(char *argv[], t_externs *externs)
{
	char	*pathname;

	if (externs->env_arr)
	{
		free_double_arr(externs->env_arr);
	}
	externs->env_arr = env_lst2arr(externs->env_lst);
	pathname = get_pathname(externs->env_arr, argv[0]);
	if (execve(pathname, argv, externs->env_arr) == -1)
	{
		ft_putendl_fd("command not found", 2);
		exit(1);
	}
	return (0);
}
