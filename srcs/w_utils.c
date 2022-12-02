
#include "parse.h"


void print(void *ptr)
{
	char *str = (char *)ptr;

	printf("[%s] ", str);
}

void	print_cmd_arr(t_cmd_info *cmd_info_arr, int pipe_num)
{
	printf("-------------------------------\n");
	for (int i = 0; i <= pipe_num; i++) {
		printf("argc: %d\n", cmd_info_arr[i].argc);
		printf("argv: ");
		for (int j = 0; cmd_info_arr[i].argv[j]; j++)
			printf("[%s] ", cmd_info_arr[i].argv[j]);
		printf("\n");
		printf("redir_num: %d\n", cmd_info_arr[i].redir_num);
		printf("redir: ");
		for (int j = 0; cmd_info_arr[i].redir[j].type; j++)
			printf("[%d, %s] ", cmd_info_arr[i].redir[j].type, cmd_info_arr[i].redir[j].str);
		printf("\n");
		printf("here: ");
		for (int j = 0; cmd_info_arr[i].here[j]; j++)
			printf("[%s] ", cmd_info_arr[i].here[j]);
		printf("\n");
		printf("-------------------------------\n");
	}
}