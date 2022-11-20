#include "minishell.h"

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
	execve(pathname, argv, 0);
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
