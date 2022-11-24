#include "minishell.h"

void var_name_err(void) {
	ft_putstr_fd("not a vlaid identifier\n", 2);
	return ;
}

void chk_fork_err(int pid) {
	if (pid < 0) {
		ft_putstr_fd("Faild to for child process\n", 2);
		exit(1);
	}
	return ;
}

void chk_fd_err(int fd) {
	if (fd < 0) {
		ft_putstr_fd("Failed to open file\n", 2);
		exit(1);
	}
	return ;
}
