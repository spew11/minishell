#include "minishell.h"

int main(int argc, char *argv[], char *envp[]) {
	char *line;
	struct termios term;
	t_cmd_info *cmd_infos;
	tcgetattr(0, &term);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(0, TCSANOW, &term);
	signal_on();

	int			pipe_num;
	t_cmd_info	*cmd_arr;
	t_var_lst *env_lst;
	env_lst = init_var_lst(envp);
	while (1) {
		line = readline("minishell$ ");
		if (!line) {
			printf("\033[1A");
			printf("\033[11C");
			printf("exit\n");
			exit(1);
		}
		if (*line == '\0') {
			free(line);
		}
		else if (line) {
			if (strcmp(line, "exit") == 0) {
				break;
			}
			add_history(line);
			cmd_arr = parse_line(line, &pipe_num, envp);
			run_cmds(cmd_arr, pipe_num, env_lst);
			free(line);
		}
	}
	return (0);
}

/*
int main(int argc, char *argv[], char *envp[])
{
	char		*line;
	int			pipe_num;
	t_cmd_info	*cmd_arr;
	t_var_lst *env_lst;
	env_lst = init_var_lst(envp);
	
	line = readline("minishell$ ");

	cmd_arr = parse_line(line, &pipe_num, envp);
	run_cmds(cmd_arr, pipe_num, env_lst);
	// recur(cmd_arr, envp, pipe_num, 0, -1);
}*/
