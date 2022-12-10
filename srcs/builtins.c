#include "minishell.h"

void	ft_exit(int argc, char *argv[])
{
	ft_putendl_fd("exit", 1);
	if (argc > 1)
	{
		ft_putendl_fd("numeric argument required", 2);
		exit(2);
	}
	exit(0);
}

int	echo(int argc, char *argv[], t_var_lst *env_lst)
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

int	cd_to_path(char *argv[], char *home_path, char **paths)
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
	ret = cd_to_path(argv, home_path, paths);
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

static int	export_add_var(char *s, t_var_lst **env_lst, t_var_lst **export_lst)
{
	char	**var_val;

	var_val = ft_slice(s, '=');
	if (var_val)
	{
		if (!var_val[0] || (var_val[0] && chk_var_name(var_val[0])))
		{
			ft_putendl_fd("not a valid identifier", 2);
			return (1);
		}
		if (var_val[1] == 0)
			var_val[1] = ft_strdup("\"\"");
		if (!chk_var_name(var_val[0]))
		{
			add_var_lst(export_lst, var_val[0], var_val[1]);
			add_var_lst(env_lst, var_val[0], var_val[1]);
		}
		free(var_val);
		return (0);
	}
	if (!chk_var_name(s))
		add_var_lst(export_lst, s, 0);
	else
		return (1);
	return (0);
}

int	export(int argc, char *argv[], t_var_lst **env_lst, t_var_lst **export_lst)
{
	int		ret;
	int		i;

	ret = 0;
	if (argc == 1)
		print_var_lst(*export_lst);
	else
	{
		i = 1;
		while (argv[i])
		{
			ret = export_add_var(argv[i], env_lst, export_lst);
			sort_var_lst(*export_lst);
			i++;
		}
	}
	return (ret);
}

int	unset(int argc, char *argv[], t_var_lst **env_lst, t_var_lst **export_lst)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!chk_var_name(argv[i]))
		{
			remove_var_lst(export_lst, argv[i]);
			remove_var_lst(env_lst, argv[i]);
		}
		i++;
	}
	return (0);
}

int	env(int argc, char *argv[], t_var_lst *env_lst)
{
	if (argc != 1)
	{
		ft_putendl_fd("too many arguments", 2);
		return (1);
	}
	print_var_lst(env_lst);
	return (0);
}
