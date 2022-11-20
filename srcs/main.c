#include "minishell.h"
/*int main(int argc, char *argv[], char *envp[]) {
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
}*/
//test main code
int main(int argc, char *argv[], char *envp[]) {
	t_cmd_info **cmd_infos;

	cmd_infos = (t_cmd_info **)malloc(sizeof(t_cmd_info*) * 3);
	for (int i = 0; i < 2; i++) {
		cmd_infos[i] = (t_cmd_info *)malloc(sizeof(t_cmd_info));
	}
	cmd_infos[2] = 0;
	cmd_infos[0]->argv = ft_split("echo happy", ' ');
	cmd_infos[0]->argc = 1;
	cmd_infos[0]->in_type = 0;
	cmd_infos[0]->in_str = 0;
	cmd_infos[0]->out_type = FILE_END;
	cmd_infos[0]->out_str = "out1";
	
	cmd_infos[1]->argv = 0;
	cmd_infos[1]->argc = 0;
	cmd_infos[1]->in_type = FILE;
	cmd_infos[1]->in_str = "out1";
	cmd_infos[1]->out_type = FILE_END;
	cmd_infos[1]->out_str = "out2";
	run_cmds(cmd_infos, envp);
}
