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
	t_env_lst env_lst;
	t_env_lst export_lst;
	init_env_lst(&env_lst, envp);
	init_env_lst(&export_lst, envp);
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
			//cmd_infos = parsing line&initiate_infos(cmd_infos);
			//run_cmds(cmd_infos);
			char **strs = ft_split(line, ' ');
			if (ft_strncmp(strs[0], "cd", 2) == 0) {
				cd(2, strs); //cd는 fork()해서 하면 안됨(binary file이 아님)
			}
			else {
				int pid = fork();
				chk_fork_err(pid);
				if (pid == 0) {
					ft_execve(strs, envp);
				}
				else {
					wait(0);
				}
			}
			free(line);
		}
	}
	return (0);
}*/

int main(int argc, char *argv[], char *envp[]) {
	t_var_lst *export_lst = init_var_lst(envp);
	t_var_lst *env_lst = init_var_lst(envp);
	export(2, ft_split("export Eunji=", ' '), export_lst, env_lst);
	export(2, ft_split("export hansu=eunji", ' '), export_lst, env_lst);
	export(4, ft_split("export apple grape=mine $hap=do", ' '), export_lst, env_lst);
	print_var_lst(export_lst);
	return (0);
}
