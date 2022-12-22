/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:06:59 by eunjilee          #+#    #+#             */
/*   Updated: 2022/12/22 17:34:08 by eunjilee         ###   ########.fr       */
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

static void	get_path1(char **pathname, char *argv[])
{
	*pathname = argv[0];
	if (ft_access(*pathname) == -1)
	{
		ft_putendl_fd("No such file or directory", 2);
		exit(127);
	}
	return ;
}

static void	get_path2(char **pathname, char *argv[], t_var_lst *env_lst)
{
	char	**paths;
	char	*tmp;
	int		i;

	paths = ft_split(ft_getenv(env_lst, "PATH"), ':');
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (*pathname)
			free(*pathname);
		*pathname = ft_strjoin(tmp, argv[0]);
		free(tmp);
		if (ft_access(*pathname) == 0)
			return ;
	}
	return ;
}

int	ft_execve(char *argv[], t_externs *externs)
{
	char	*pathname;
	char	**argv_arr;

	signal(SIGQUIT, SIG_DFL);
	pathname = 0;
	argv_arr = ft_split(argv[0], '/');
	if (externs->env_arr)
		free_double_arr(externs->env_arr);
	externs->env_arr = env_lst2arr(externs->env_lst);
	if ((argv[0][0] == '/') || !ft_strncmp(argv_arr[0], ".", -1) ||
		!ft_strncmp(argv_arr[0], "..", -1))
		get_path1(&pathname, argv);
	else
		get_path2(&pathname, argv, externs->env_lst);
	if (execve(pathname, argv, externs->env_arr) == -1)
	{
		ft_putendl_fd("command not found", 2);
		exit(1);
	}
	return (0);
}
