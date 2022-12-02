#include "minishell.h"

int minishell(t_externs *externs) {
	int ret = 0;
	char	*line;
	int		pipe_num;
	t_cmd_info	*cmd_infos;

	while (1) {
		line = readline("minishell$ ");
		if (!line) {
			//printf("\033[1A");
			//printf("\033[11C");
			printf("exit\n");
			return (0);
		}
		if (*line == '\0') {
			free(line);
		}
		else if (line) {
			if (ft_strncmp(line, "exit", -1) == 0) {
				return (0);
			}
			add_history(line);
			cmd_infos = parse_line(line, &pipe_num, externs->env_lst);
			here_doc(cmd_infos, pipe_num);
			ret = run_cmds(cmd_infos, pipe_num, externs);
			free(line);
		}
	}
	return (ret);
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
	t_externs externs;
	externs.env_lst = init_var_lst(envp);
	externs.export_lst = init_var_lst(envp);
	externs.env_arr = env_lst2arr(externs.env_lst);
	ret = minishell(&externs);
	//have to free all malloc
	return (ret);
}
