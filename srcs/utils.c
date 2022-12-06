#include "minishell.h"

void free_double_arr(char **arr) {
	int i = 0;
	while (arr[i]) {
		free(arr[i]);
		i++;
	}
	free(arr);
	return ;
}

int is_builtin(char *cmd) {
	if (ft_strncmp(cmd, "echo", -1) == 0)
		return 1;
	if (ft_strncmp(cmd, "cd", -1) == 0)
		return 1;
	if (ft_strncmp(cmd, "pwd", -1) == 0)
		return 1;
	if (ft_strncmp(cmd, "export", -1) == 0)
		return 1;
	if (ft_strncmp(cmd, "unset", -1) == 0)
		return 1;
	if (ft_strncmp(cmd, "env", -1) == 0)
		return 1;
	if (ft_strncmp(cmd, "exit", -1) == 0)
		return 1;
	return 0;
}

int exec_builtin(int argc, char *argv[], t_var_lst *env_lst, t_var_lst *export_lst) {
	if (ft_strncmp(argv[0], "echo", -1) == 0)
		return echo(argc, argv, env_lst);
	if (ft_strncmp(argv[0], "cd", -1) == 0)
		return cd(argc, argv, env_lst);
	if (ft_strncmp(argv[0], "pwd", -1) == 0)
		return pwd();
	if (ft_strncmp(argv[0], "export", -1) == 0)
		return export(argc, argv, &env_lst, &export_lst);
	if (ft_strncmp(argv[0], "unset", -1) == 0)
		return unset(argc, argv, &env_lst, &export_lst);
	if (ft_strncmp(argv[0], "env", -1) == 0)
		return env(argc, argv, env_lst);
	if (ft_strncmp(argv[0], "exit", -1) == 0)
		ft_exit(argc, argv);
	return 1;
}

int chk_var_name(char *var_name) {
	int i = 0;
	while (var_name[i]) {
		if (i == 0 && ft_isdigit(var_name[i])) {
			ft_putendl_fd("not a valid identifier", 2);
			return (0);
		}
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_') {
			ft_putendl_fd("not a valid identifier", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

char **ft_slice(char *str, char sep) {
	char **strs;
	int i = 0;
	int sep_idx = 0;
	size_t str_len = ft_strlen(str);
	while (str[i]) {
		if (str[i] == sep) {
			sep_idx = i;
			break;
		}
		i++;
	}
	if (i == str_len) {
		return (0);
	}
	strs = (char **)malloc(sizeof(char *) * 3);
	strs[2] = 0;
	strs[0] = (char *)malloc(sizeof(char) * (sep_idx + 1));
	strs[1] = (char *)malloc(sizeof(char) * (str_len - sep_idx));
	ft_strlcpy(strs[0], str, sep_idx + 1);
	ft_strlcpy(strs[1], str + sep_idx + 1, str_len - sep_idx);
	return (strs);
}

int ft_access(const char *pathname) {
	struct stat statbuf;
	if (stat(pathname, &statbuf) == 0) {
		return (0);
	}
	return (-1);
}

static char *get_pathname(char *envp[], char *filename) {
	char *pathname = 0;
	for (int i = 0; envp[i]; i++) {
		char *paths = ft_strchr(envp[i], '=') + 1;
		char **path = ft_split(paths, ':');
		for (int j = 0; path[j]; j++) {
			char *tmp = ft_strjoin(path[j], "/");
			if (!pathname) {
				free(pathname);
			}
			pathname = ft_strjoin(tmp, filename);
			free(tmp);
			if (ft_access(pathname) == 0) {
				return (pathname);
			}
		}
	}
	return (0);
}

int ft_execve(char *argv[], t_externs *externs) {
	if (externs->env_arr) {
		free_double_arr(externs->env_arr);
	}
	externs->env_arr = env_lst2arr(externs->env_lst);
	char *pathname = get_pathname(externs->env_arr, argv[0]);
	if (execve(pathname, argv, externs->env_arr) == -1) {
		ft_putendl_fd(strerror(errno), 2);
		exit (1);
	}
	return (0);
}

void sig_handler(int signal) {
	pid_t pid;
	int	status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signal == SIGINT) {
		if (pid == -1) {
			printf("\n");
			if (rl_on_new_line() == -1)
				exit(1);
			rl_replace_line("", 1);
			rl_redisplay();
			exit_status = 1;
		}
		else {
			printf("\n");
			return ;
		}
	}
	return ;
}

void signal_on() {
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
