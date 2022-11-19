#include "minishell.h"

int echo(char *cmd_info[]) {
	int option_flag = 0;
	int i = 1;
	if (strcmp(cmd_info[i], "-n") == 0) {
		option_flag = 1;
		i++;
	}


	return (0);
}
