#include "minishell.h"

static int run_func(int argc, char *argv[], char *envp[]) {
	if (argc == 0) {
		argv = ft_split("cat", ' ');
		//ex. echo happy > out1 > out2
	}
	ft_execve(argv, envp);
	return (0);
}

static int run_cmd(t_cmd_info **cmd_infos, int idx, char *envp[]) {
	int in_fd = 0;
	int out_fd = 0;

	if (cmd_infos[idx]->in_str) {
		/*test code
		int tmp_fd = open("tmp", O_WRONLY | O_APPEND | O_CREAT, 0644);
		dprintf(tmp_fd, "%s\n", cmd_infos[idx]->in_str);*/
		if (ft_access(cmd_infos[idx]->in_str) == -1) {
			ft_putstr_fd("No such file or derectory\n", 2);
			exit(1);
		}
		in_fd = open(cmd_infos[idx]->in_str, O_RDONLY, 0644);
		chk_fd_err(in_fd);
		dup2(in_fd, 0);
	}
	if (cmd_infos[idx]->out_str) {
		if (cmd_infos[idx]->out_type == FILE) {
			out_fd = open(cmd_infos[idx]->out_str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		}
		else if (cmd_infos[idx]->out_type == FILE_END) {
			out_fd = open(cmd_infos[idx]->out_str, O_WRONLY | O_APPEND | O_CREAT, 0644);
		}
		chk_fd_err(out_fd);
		dup2(out_fd, 1);
	}
	if (cmd_infos[idx]->out_type == PIPE) {
		int fd[2];
		if (pipe(fd) < 0) {
			exit(1);
		}
		int pid = fork();
		chk_fork_err(pid);
		if (pid == 0) {
			close(fd[1]);
			dup2(fd[0], 0);
			run_cmd(cmd_infos, idx + 1, envp);
		}
		else {
			close(fd[0]);
			dup2(fd[1], 1);
			run_func(cmd_infos[idx]->argc, cmd_infos[idx]->argv, envp);
		}
	}
	int pid = fork();
	chk_fork_err(pid);
	if (pid == 0) {
		run_func(cmd_infos[idx]->argc, cmd_infos[idx]->argv, envp);
	}
	else {
		if (cmd_infos[idx + 1]) {
			run_cmd(cmd_infos, idx + 1, envp);
		}
	}
	return 0;
}

int run_cmds(t_cmd_info **cmd_infos, char *envp[]) {
	int pid = fork();
	chk_fork_err(pid);
	if (pid == 0) {
		run_cmd(cmd_infos, 0, envp);
	}
	else {
		if (wait(0) != pid) {
			exit(1);
		}
	}
	return (0);
}
