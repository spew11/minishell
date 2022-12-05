#include "minishell.h"

static void	unlink_tmpfiles(t_cmd_info *cmd_infos, int pipe_num)
{
	int	i;
	int	j;

	i = 0;
	while (i <= pipe_num)
	{
		j = 0;
		while (j < cmd_infos[i].here_num)
		{
			if (unlink(cmd_infos[i].here[j]) < 0)
			{
				exit_status = -1;
			}
			j++;
		}
		i++;
	}
	return ;
}

static void	wait_pids(pid_t *pid_arr, int pipe_num)
{
	int	status;
	int	idx;

	if (pipe_num >= 0)
	{
		if (waitpid(pid_arr[pipe_num], &status, 0) != pid_arr[pipe_num])
			exit_status = 1;
		exit_status = WEXITSTATUS(status);
		idx = 0;
		while (idx < pipe_num)
		{
			if (waitpid(pid_arr[idx], 0, 0) != pid_arr[idx])
				exit_status = 1;
			idx++;
		}
	}
	return ;
}

static int	run_cmd(t_cmd_info *cmd_info, t_externs *externs)
{
	int in_fd = -1;
	int out_fd = -1;
	int type = 0;
	char *filename;
	int ret = 0;

	int i = 0;
	while (i < cmd_info->redir_num) {
		type = cmd_info->redir[i].type;
		filename = cmd_info->redir[i].str;
		if (type == INFILE || type == HERE_DOC) {
			if (ft_access(filename) == -1) {
				ft_putendl_fd(strerror(errno), 2);
				return (1);
			}
			if (in_fd != -1) {
				close(in_fd);
			}
			in_fd = open(filename, O_RDONLY, 0644);
			if (in_fd < 0) {
				ft_putendl_fd("Failed to open file", 2);
				return (1);
			}
			dup2(in_fd, 0);
		}
		else {
			if (type == OUTFILE) {
				if (out_fd != -1) {
					close(out_fd);
				}
				out_fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			}
			else if (type == FILE_APPEND) {
				if (out_fd != -1) {
					close(out_fd);
				}
				out_fd = open(filename, O_WRONLY | O_TRUNC | O_APPEND | O_CREAT, 0644);
			}
			if (out_fd < 0) {
				ft_putendl_fd("Failed to open file", 2);
				return (1);
			}
			dup2(out_fd, 1);
		}
		i++;
	}
	int status;
	if (cmd_info->argc == 0) {
		ret = 0;
	}
	else {
		if (is_builtin(cmd_info->argv[0])) {
			ret = exec_builtin(cmd_info->argc, cmd_info->argv, externs->env_lst, externs->export_lst);
		}
		else {
			int pid = fork();
			if (pid < 0) {
				ft_putendl_fd(strerror(errno), 2);
				return (1);
			}
			if (pid == 0) {
				ft_execve(cmd_info->argv, externs->env_arr);
			}
			else {
				if (waitpid(pid, &status, 0) != pid) {
					ft_putendl_fd(strerror(errno), 2);
					return (1);
				}
				ret = WEXITSTATUS(status);
				printf("%d\n", ret);
			}
		}
	}
	close(in_fd);
	close(out_fd);
	return (ret);
}

void	run_cmd_without_pipe(t_cmd_info *cmd_infos, int idx, t_externs *externs)
{
	int	temp[2];

	temp[0] = dup(0);
	temp[1] = dup(1);
	exit_status = run_cmd(cmd_infos + idx, externs);
	dup2(temp[0], 0);
	dup2(temp[1], 1);
	return ;
}

int	run_cmd_with_pipe(t_cmd_info *cmd_infos, int pipe_num, int idx,
	t_shell_info *shell_info)
{
	shell_info->pid_arr[idx] = fork();
	if (shell_info->pid_arr[idx] < 0)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	if (shell_info->pid_arr[idx] == 0)
	{
		if (idx < pipe_num)
		{
			dup2(shell_info->out_fd[1], 1);
			close(shell_info->out_fd[0]);
		}
		if (shell_info->in_fd != -1) {
			dup2(shell_info->in_fd, 0);
			close(shell_info->in_fd);
		}
		exit(run_cmd(cmd_infos + idx, shell_info->externs));
	}
	else {
		if (idx > 0) {
			close(shell_info->in_fd);
		}
		if (idx < pipe_num) {
			shell_info->in_fd = shell_info->out_fd[0];
			close(shell_info->out_fd[1]);
		}
	}
	return (0);
}

int	run_cmds(t_cmd_info *cmd_infos, int pipe_num, t_shell_info *shell_info)
{
	int	idx;

	shell_info->in_fd = -1;
	shell_info->pid_arr = (int *)malloc(sizeof(int) * (pipe_num + 1));
	if (shell_info->pid_arr < 0)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (-1);
	}
	idx = 0;
	while (idx <= pipe_num)
	{
		if (idx < pipe_num)
			pipe(shell_info->out_fd);
		if (pipe_num == 0)
			run_cmd_without_pipe(cmd_infos, idx, shell_info->externs);
		else
			if (run_cmd_with_pipe(cmd_infos, pipe_num, idx, shell_info))
				return (1);
		idx++;
	}
	wait_pids(shell_info->pid_arr, pipe_num);
	unlink_tmpfiles(cmd_infos, pipe_num);
	free(shell_info->pid_arr);
	return (0);
}
