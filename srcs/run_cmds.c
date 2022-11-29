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
}

int run_cmds(t_cmd_info *cmd_infos, int pipe_num, int idx, t_externs *externs)
{
	int in_fd = 0;
	int out_fd = 1;
	int type = 0;
	char *filename;
	
	//set input output
	int i = 0;
	while (i < cmd_infos[idx].redir_num) {
		type = cmd_infos[idx].redir[i].type;
		filename = cmd_infos[idx].redir[i].str;
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
	/**************************************************************************/
	if (is_builtin(cmd_infos[idx].argv[0])) {
		//not fork
		if (idx < pipe_num) {
			int fd[2];
			pipe(fd);
			int ret = fork();
			if (ret == 0) {
				close(fd[1]);
				dup2(fd[0], 0);
				run_cmds(cmd_infos, pipe_num, idx + 1, externs);
			}
			else {
				//여기는 기존 프로세스임
				close(fd[0]);
				dup2(fd[1], out_fd);
				exec_builtin(cmd_infos[idx].argc, cmd_infos[idx].argv, externs->env_lst, externs->export_lst);
			}
		}
		else {
			exec_builtin(cmd_infos[idx].argc, cmd_infos[idx].argv, externs->env_lst, externs->export_lst);
		}
	}
	else {
		//fork
		int status;
		int ret = fork();
		if (ret == 0) {
			if (idx < pipe_num) {
				int fd2[2];
				pipe(fd2);
				int status2;
				int ret2 = fork();
				if (ret2 == 0) {
					close(fd2[1]);
					dup2(fd2[0], 0);
					run_cmds(cmd_infos, pipe_num, idx + 1, externs);
				}
				else {
					close(fd2[0]);
					dup2(fd2[1], out_fd);
					ft_execve(cmd_infos[idx].argv, externs->env_arr);
					wait(&status2);
				}
			}
			else {
				ft_execve(cmd_infos[idx].argv, externs->env_arr);
			}
		}
		else {
			wait(&status);
			//미니쉘 입력 기다리는 곳임 죽으면 안됨
		}
	}
	return (0);
}
