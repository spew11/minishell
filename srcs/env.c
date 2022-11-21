#include "minishell.h"

int init_env_lst(t_env_lst *env_lst, char *envp[]) {
	int i = 0;
	t_env_lst *now = env_lst;
	while (envp[i]) {
		now->env_val = ft_slice(envp[i], '=');
		now->next = (t_env_lst *)malloc(sizeof(t_env_lst) * 1);
		now->next->next = 0;
		now = now->next;
		i++;
	}
	// test print
	now = env_lst;
	while (now->next) {
		printf("%s", now->env_val[0]);
		printf("=");
		printf("%s\n", now->env_val[1]);
		now = now->next;
	} 
	return (0);
}
