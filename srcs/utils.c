#include "minishell.h"

int chk_var_name(char *var_name) {
	int i = 0;
	while (var_name[i]) {
		if (i == 0 && ft_isdigit(var_name[i])) {
			var_name_err();
			return (0);
		}
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_') {
			var_name_err();
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
	strs[0] = (char *)malloc(sizeof(char) * (sep_idx));
	strs[1] = (char *)malloc(sizeof(char) * (str_len - sep_idx + 1));
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
	ft_putstr_fd("command not found\n", 2);
	exit(1);
	return (0);
}

void ft_execve(char *argv[], char *envp[]) {
	char *pathname = get_pathname(envp, argv[0]);
	execve(pathname, argv, envp);
	return ;
}

void sig_handler(int signal) {
	if (signal == SIGINT) {
		printf("\n");
	}
	if (rl_on_new_line() == -1) {
		exit(1);
	}
	rl_replace_line("", 1);
	rl_redisplay();
}

void signal_on() {
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
