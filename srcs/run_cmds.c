#include "minishell.h"

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
	if (ft_strncmp(cmd, "print_exit", -1) == 0)
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
		return ft_exit(argc, argv);
	if (ft_strncmp(argv[0], "print_exit", -1) == 0)
		return print_exit();
	return 1;
}

int run_cmd(t_cmd_info *cmd_info, t_externs *externs)
{
	int in_fd;
	int out_fd;
	int type = 0;
	char *filename;
	int ret = 0;
	//set input output
	int i = 0;
	while (i < cmd_info->redir_num) {
		type = cmd_info->redir[i].type;
		filename = cmd_info->redir[i].str;
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
	if (is_builtin(cmd_info->argv[0])) {
		ret = exec_builtin(cmd_info->argc, cmd_info->argv, externs->env_lst, externs->export_lst);
	}
	else {
		ft_execve(cmd_info->argv, externs->env_arr);
	}
	exit(ret);
	return (0);
}


int run_cmds(t_cmd_info *cmd_infos, int pipe_num, t_externs *externs) {
	int in_fd = -1;
	int tmp_fd = -1;
	int out_fd[2] = {0, 1};
	int idx = 0;
	while (idx <= pipe_num) {
		if (idx < pipe_num) { // idx번째 프로세스 뒤에 pipe가 있음
			pipe(out_fd);
		}
		if (idx == 0 && is_builtin(cmd_infos[idx].argv[0])) {
			if (pipe_num > 0) {
				tmp_fd = dup(1);
				dup2(out_fd[1], 1);
			}
			exit_status = exec_builtin(cmd_infos[idx].argc, cmd_infos[idx].argv, externs->env_lst, externs->export_lst);
			if (pipe_num > 0) {
				dup2(tmp_fd, 1);
				close(out_fd[1]);
				in_fd = out_fd[0];
			}
		}
		else {
			pid_t pid = fork();
			int status;
			if (pid == 0) {
				if (idx < pipe_num) {
					dup2(out_fd[1], 1);  // 내(방금 포크 뜬 자식 프로세스) 출력은 STDOUT이 아니라, out_fd[1]에 갈 거야
					close(out_fd[0]);
				}
				if (in_fd != -1) {
					dup2(in_fd, 0);  // 내(방금 포크 뜬 자식 프로세스)의 입력은 STDIN이  아니라, in_fd(지난번 while step에서의 out_fd[0])에서 가져올거야
				}
				run_cmd(cmd_infos + idx, externs);
			}
			else {
				int end_pid = waitpid(pid, &status, 0);
				if (end_pid != pid) {
					return (1);
				}
				else {
					exit_status = WEXITSTATUS(status);
				}
				if (idx < pipe_num) {
					in_fd = out_fd[0];
					close(out_fd[1]);
				}
			}
		}
		if (exit_status != 0) {
			return (exit_status);
		}
		idx++;
	}
	return (0);
}
