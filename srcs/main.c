#include "minishell.h"
/*
int main(int argc, char *argv[], char *envp[]) {
	char *line;
	struct termios term;
	t_cmd_info *cmd_infos;
	tcgetattr(0, &term);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(0, TCSANOW, &term);
	signal_on();
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
			* cmd_infos = parsing line&initiate_infos(cmd_infos);
			* run_cmds(cmd_infos);
			printf("%s\n", line);
			free(line);
		}
	}
	return (0);
}
*/

int main(int argc, char *argv[], char *envp[]) {
	ft_execve(argv + 1, envp);
	return (0);
}


