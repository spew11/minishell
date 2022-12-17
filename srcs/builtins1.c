/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:06:05 by eunjilee          #+#    #+#             */
/*   Updated: 2022/12/17 17:41:07 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(int argc)
{
	ft_putendl_fd("exit", 1);
	if (argc > 1)
	{
		ft_putendl_fd("numeric argument required", 2);
		exit(2);
	}
	exit(0);
}

int	echo(int argc, char *argv[])
{
	char	*str;
	int		opt_f;
	int		i;

	opt_f = 0;
	i = 1;
	if (argc > 1 && ft_strncmp(argv[1], "-n", 2) == 0)
	{
		opt_f = 1;
		i++;
	}
	while (i < argc)
	{
		str = argv[i];
		printf("%s", str);
		if (i < argc - 1)
			printf(" ");
		i++;
	}
	if (!opt_f)
	{
		printf("\n");
	}
	return (0);
}

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
	paths = ft_split(argv[1], '/');
	ret = cd_to_path(home_path, paths);
	free_double_arr(paths);
	return (ret);
}

int	pwd(void)
{
	char	buf[4096];

	getcwd(buf, 4096);
	printf("%s\n", buf);
	return (0);
}
