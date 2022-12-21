/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:06:05 by eunjilee          #+#    #+#             */
/*   Updated: 2022/12/21 23:50:56 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_err(char *str, int ret)
{
	ft_putendl_fd(str, 2);
	exit(ret);
	return ;
}

void	ft_exit(int argc, char *argv[])
{
	int	i;
	int	argv_f;

	argv_f = 1;
	ft_putendl_fd("exit", 1);
	if (argc == 1)
		exit(0);
	i = -1;
	while (argv[1][++i])
	{
		if (!ft_isdigit(argv[1][i]))
		{
			argv_f = 0;
			break;
		}
	}
	if (argv_f)
	{
		if (argc == 2)
			exit(ft_atoi(argv[1]));
		else
			exit_err("too many arguments", 1);
	}
	exit_err("numieric argument required", 2);
	return ;
}

static void echo_opt(char *argv[], int *i, int *opt_f, int b_flag)
{
	int	j;

	while (argv[++(*i)])
	{
		if (argv[*i][0] != '-')
			break;
		else
		{
			b_flag = 0;
			j = 0;
			while (argv[*i][++j])
			{
				if (argv[*i][j] != 'n')
				{
					b_flag = 1;
					break;
				}
			}
			if (b_flag == 1)
				break;
			*opt_f = 1;
		}
		if (b_flag == 1)
			break;
	}
}

int	echo(int argc, char *argv[])
{
	int	opt_f;
	int	i;

	opt_f = 0;
	i = 0;
	echo_opt(argv, &i, &opt_f, 0);
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i < argc - 1)
			printf(" ");
		i++;
	}
	if (!opt_f)
		printf("\n");
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
	if (argv[1][0] == '/')
		chdir("/");
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
