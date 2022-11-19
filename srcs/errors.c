#include "minishell.h"

void chk_fork_err(int pid) {
	if (pid < 0) {
		ft_putstr_fd("Faild to for child process\n", 2);
		exit(1);
	}
	return ;
}

void chk_fd_err(int fd) {
	if (fd < 0) {
		ft_putstr_fd("no such file or derectory\n", 2);
		exit(1);
	}
	return ;
}
