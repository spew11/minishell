#include "minishell.h"

int run_cmd(t_cmd_info *cmd_info) {
	/*if in_str == 0, doesn't set input*/
	if (!(cmd_info->in_str)) {
			int in_fd = open(in_str, O_RDONLY, 0644);
			chk_fd_err(in_fd);
			dup2(in_str, 0);
		}
	}
	/*if in_out == 0, doesn't set output*/
	if (!(cmd_info->out_str)) {
			int out_fd = open(out_str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			chk_fd_err(out_fd);
			dup2(out_str, 1);
		}
	}
	if (out_type == PIPE) {
		int fd[2];
		if (pipe(fd) < 0) {
			exit(1);
		}
		int pid = fork();
		chk_fork_err(pid);
		if (pid == 0) {
			close(fd[1]);
			dup2(fd[0], 0);
			run_cmd(cmd_info + 1);
		}
		else {
			close(fd[0]);
			dup2(fd[1], 1);
			//run_func(cmd_info->argc, cmd_info->argv);
		}
		/*run_func(cmd_info->argc, cmd_info->argv);
		 if (*(cmd_info + 1)) {
			run_cmd(cmd_info + 1);
		}*/
	}
	return 0;
}

int run_cmds(t_cmd_info *cmd_infos) {
	int pid = fork();
	chk_fork_err(pid);
	if (pid == 0) {
		run_cmd(&cmd_infos[0]);
	}
	else {
		if (wait(0) != pid) {
			exit(1);
		}
	}
	return (0);
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