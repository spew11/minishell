#include "minishell.h"

int minishell(t_externs *externs) {
	char	*line;
	int		pipe_num;
	t_cmd_info	*cmd_infos;

	t_shell_info shell_info;
	shell_info.exit_flag = 0;
	while (1) {
		line = readline("minishell$ ");
		if (!line) {
			printf("\033[1A");
			printf("\033[11C");
			printf("exit\n");
			return (0);
		}
		if (*line == '\0') {
			printf("here\n");
			free(line);
		}
		else if (line) {
			add_history(line);
			cmd_infos = parse_line(line, &pipe_num, externs->env_arr);
			run_cmds(cmd_infos, pipe_num, 0, externs);
			free(line);
		}
	}
	return (0);
}

int main(int argc, char *argv[], char *envp[]) {
	if (argc > 2) {
		return (127);
	}
	struct termios term;
	tcgetattr(0, &term);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(0, TCSANOW, &term);
	signal_on();
	
	t_externs externs;
	externs.env_lst = init_var_lst(envp);
	externs.export_lst = init_var_lst(envp);
	externs.env_arr = env_lst2arr(externs.env_lst);
	minishell(&externs);
	//have to free all malloc
	return (0);
}
