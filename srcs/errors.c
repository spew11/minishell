#include "minishell.h"

void chk_fork_err(int pid) {
	if (pid < 0) {
		ft_putstr_fd("Faild to for child process\n", 2);
		exit(1);
	}
	return ;
}
