#include "minishell.h"

int minishell(t_shell_info *shell_info) {
	int ret = 0;
	char	*line;
	int		pipe_num;
	t_cmd_info	*cmd_infos;

	while (1) {
		line = readline("minishell$ ");
		if (!line) {
			printf("exit\n");
			return (0);
		}
		if (*line == '\0') {
			free(line);
		}
		else if (line) {
			add_history(line);
			cmd_infos = parse_line(line, &pipe_num, shell_info->externs->env_lst);
			if (cmd_infos) {
				ret = run_cmds(cmd_infos, pipe_num, shell_info);
				free(line);
				//free_cmd_infos;
			}
		}
	}
	return (ret);
}

void clear_shell_info(t_shell_info *shell_info) {
	clear_var_lst(shell_info->externs->env_lst);
	clear_var_lst(shell_info->externs->export_lst);
	free_double_arr(shell_info->externs->env_arr);
	return ;
}

int main(int argc, char *argv[], char *envp[]) {
	int ret = 0;
	if (argc > 2) {
		return (127);
	}
	struct termios term;
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &term);
	signal_on();
	exit_status = 0;
	t_shell_info shell_info;
	shell_info.externs = (t_externs *)malloc(sizeof(t_externs) * 1);
	if (shell_info.externs < 0) {
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	shell_info.externs->env_lst = init_var_lst(envp);
	shell_info.externs->export_lst = init_var_lst(envp);
	shell_info.externs->env_arr = 0;
	ret = minishell(&shell_info);
	clear_shell_info(&shell_info);
	return (ret);
}
