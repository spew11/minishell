#include "minishell.h"

void	free_double_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return ;
}

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", -1) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", -1) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", -1) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", -1) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", -1) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", -1) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", -1) == 0)
		return (1);
	return (0);
}

int	exec_builtin(int argc, char *argv[],
		t_var_lst **env_lst, t_var_lst **export_lst)
{
	if (ft_strncmp(argv[0], "echo", -1) == 0)
		return (echo(argc, argv, *env_lst));
	if (ft_strncmp(argv[0], "cd", -1) == 0)
		return (cd(argc, argv, *env_lst));
	if (ft_strncmp(argv[0], "pwd", -1) == 0)
		return (pwd());
	if (ft_strncmp(argv[0], "export", -1) == 0)
		return (export(argc, argv, env_lst, export_lst));
	if (ft_strncmp(argv[0], "unset", -1) == 0)
		return (unset(argc, argv, env_lst, export_lst));
	if (ft_strncmp(argv[0], "env", -1) == 0)
		return (env(argc, argv, *env_lst));
	if (ft_strncmp(argv[0], "exit", -1) == 0)
		(ft_exit(argc, argv));
	return (1);
}

int	chk_var_name(char *var_name)
{
	int	i;

	i = 0;
	while (var_name[i])
	{
		if (i == 0 && ft_isdigit(var_name[i]))
		{
			ft_putendl_fd("not a valid identifier", 2);
			return (1);
		}
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
		{
			ft_putendl_fd("not a valid identifier", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

void	null_guard_double_arr(char **arr)
{
	if (!arr)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	return ;
}

void	null_guard_arr(char *arr)
{
	if (!arr)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	return ;
}

char	**ft_slice(char *str, char sep)
{
	char	**strs;
	int		sep_idx;
	size_t	str_len;

	str_len = ft_strlen(str);
	sep_idx = 0;
	while (str[sep_idx] && str[sep_idx] != sep)
		sep_idx++;
	if (sep_idx == str_len)
		return (0);
	strs = (char **)calloc(3, sizeof(char *));
	null_guard_double_arr(strs);
	if (sep_idx != 0)
	{
		strs[0] = (char *)malloc(sizeof(char) * (sep_idx + 1));
		null_guard_arr(strs[0]);
		ft_strlcpy(strs[0], str, sep_idx + 1);
	}
	if (sep_idx != str_len - 1)
	{
		strs[1] = (char *)malloc(sizeof(char) * (str_len - sep_idx));
		null_guard_arr(strs[1]);
		ft_strlcpy(strs[1], str + sep_idx + 1, str_len - sep_idx);
	}
	return (strs);
}

int	ft_access(const char *pathname)
{
	struct stat	statbuf;

	if (stat(pathname, &statbuf) == 0)
		return (0);
	return (-1);
}

void	get_pathname_in_env(char *envp[], char *filename, char **pathname)
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

void	sig_handler(int signal)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (pid == -1)
	{
		printf("\n");
		if (rl_on_new_line() == -1)
			exit(1);
		rl_replace_line("", 1);
		rl_redisplay();
		exit_status = 1;
	}
	else
	{
		printf("\n");
	}
	return ;
}

void	signal_on(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
