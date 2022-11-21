#include "minishell.h"

int sort_var_lst(t_var_lst *var_lst) {
	t_var_lst *seat;
	t_var_lst *ptr;
	t_var_lst *min;
	seat = var_lst;

	char **tmp;
	while (seat->next) {
		min = seat;
		ptr = seat->next;
		while (ptr->next) {
			if (ft_strncmp(min->var_val[0], ptr->var_val[0], -1) > 0) {
				min = ptr;
			}
			ptr = ptr->next;
		}
		if (ft_strncmp(seat->var_val[0], min->var_val[0], -1)) {
			tmp = seat->var_val;
			seat->var_val = min->var_val;
			min->var_val = tmp;
		}
		seat = seat->next;
	}
	return (0);
}

void print_var_lst(t_var_lst *var_lst) {
	sort_var_lst(var_lst);
	t_var_lst *now = var_lst;
	while (now->next) {
		printf("%s", now->var_val[0]);
		printf("=");
		printf("%s\n", now->var_val[1]);
		now = now->next;
	}
}

int init_var_lst(t_var_lst *var_lst, char *envp[]) {
	int i = 0;
	t_var_lst *now = var_lst;
	while (envp[i]) {
		now->var_val = ft_slice(envp[i], '=');
		now->next = (t_var_lst *)malloc(sizeof(t_var_lst) * 1);
		now->next->next = 0;
		now = now->next;
		i++;
	}
	return (0);
}
