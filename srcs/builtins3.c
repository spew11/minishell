/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:18:13 by eunjilee          #+#    #+#             */
/*   Updated: 2022/12/22 15:18:15 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_to_path(char *home_path, char **paths)
{
	struct stat	statbuf;
	int			i;

	i = -1;
	while (paths[++i])
	{
		if (ft_strlen(paths[i]) == 1 && paths[i][0] == '~')
			chdir(home_path);
		else
		{
			if (stat(paths[i], &statbuf) != 0)
			{
				ft_putendl_fd(strerror(errno), 2);
				return (1);
			}
			if (!S_ISDIR(statbuf.st_mode))
			{
				ft_putendl_fd("not a directory", 2);
				return (1);
			}
			chdir(paths[i]);
		}
	}
	return (0);
}

int	cd(int argc, char *argv[], t_var_lst *env_lst)
{
	char	*home_path;
	char	**paths;
	int		ret;

	home_path = ft_getenv(env_lst, "HOME");
	if (argc == 1)
	{
		chdir(home_path);
		return (0);
	}
	else if (argc > 2)
	{
		ft_putstr_fd("too many arguments\n", 2);
		return (1);
	}
	if (argv[1][0] == '/')
		chdir("/");
	paths = ft_split(argv[1], '/');
	ret = cd_to_path(home_path, paths);
	free_double_arr(paths);
	return (ret);
}
