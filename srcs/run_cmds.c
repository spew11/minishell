#include "minishell.h"

static int run_cmd(t_cmd_info *cmd_info_arr, int pipe_num, int idx, t_var_lst *env_lst) {
	int in_fd = 0;
	int out_fd = 1;
	int type = 0;
	char *filename;
	//set input output
	int i = 0;
	while (i < cmd_info_arr[idx].redir_num) {
		type = cmd_info_arr[idx].redir[i].type;
		filename = cmd_info_arr[idx].redir[i].str;
		if (type == 1) {
			if (ft_access(filename) == -1) {
				ft_putstr_fd("No such file or directory\n", 2);
				exit(1);
			}
			in_fd = open(filename, O_RDONLY, 0644);
			chk_fd_err(in_fd);
			dup2(in_fd, 0);
		}
		else {
			if (type == 3) {
				out_fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			}
			else if (type == 4) {
				out_fd = open(filename, O_WRONLY | O_TRUNC | O_APPEND | O_CREAT, 0644);
			}
			chk_fd_err(out_fd);
			dup2(out_fd, 1);
		}
		i++;
	}
	//run_func
	if (idx < pipe_num) {
		int fd[2];
		if (pipe(fd) < 0) {
			exit(1);
		}
		pid_t pid = fork();
		chk_fork_err(pid);
		if (pid == 0) {
			close(fd[1]);
			dup2(fd[0], 0);
			run_cmd(cmd_info_arr, pipe_num, idx + 1, env_lst);
		}
		else {
			close(fd[0]);
			dup2(fd[1], out_fd);
			ft_execve(cmd_info_arr[idx].argv, env_lst);
			//unlink tmpfiles
		}
	}
	else {
		ft_execve(cmd_info_arr[idx].argv, env_lst);
		//unlink tmpfiles
	}
	return (0);
}

int run_cmds(t_cmd_info *cmd_info_arr, int pipe_num, t_var_lst *env_lst) {
	pid_t pid = fork();
	int wstatus;

	chk_fork_err(pid);
	if (pid == 0) {
		run_cmd(cmd_info_arr, pipe_num, 0, env_lst);
	}
	else {
		if (waitpid(pid, &wstatus, 0) != pid) {
			exit(wstatus);
		}
	}
	return (0);
}
