#include "minishell.h"
//넣을 때 중복검사해야됨
void add_var_lst(t_var_lst *var_lst, char *var, char *val) {
	
	t_var_lst *now;

	now = var_lst;
	while (now->next) {
		now = now->next;
	}
	now->next = (t_var_lst *)malloc(sizeof(t_var_lst) * 1);
	now->next->var = var;
	now->next->val = val;
	now->next->next = 0;
	return ;
}

void sort_var_lst(t_var_lst *var_lst) {
	t_var_lst *seat;
	t_var_lst *ptr;
	t_var_lst *min;
	seat = var_lst;

	char *var_tmp;
	char *val_tmp;
	while (seat->next) {
		min = seat;
		ptr = seat->next;
		while (ptr->next) {
			if (ft_strncmp(min->var, ptr->var, -1) > 0) {
				min = ptr;
			}
			ptr = ptr->next;
		}
		if (ft_strncmp(seat->var, min->var, -1)) {
			var_tmp = seat->var;
			val_tmp = seat->val;
			seat->var = min->var;
			seat->val = min->val;
			min->var = var_tmp;
			min->val = val_tmp;
		}
		seat = seat->next;
	}
	return ;
}

void print_var_lst(t_var_lst *var_lst) {
	t_var_lst *now = var_lst;
	while (now) {
		if (now->var && now->val) {
			printf("%s", now->var);
			printf("=");
			printf("%s\n", now->val);
		}
		else if (now->var && !now->val) {
			printf("%s\n", now->var);
		}
		now = now->next;
	}
	return ;
}

t_var_lst *init_var_lst(char *envp[]) {
	int i = 1;
	char **var_val;

	t_var_lst *now = (t_var_lst *)malloc(sizeof(t_var_lst) * 1);
	var_val = ft_slice(envp[0], '=');
	now->var = var_val[0];
	now->val = var_val[1];
	now->next = 0;
	t_var_lst *head = now;
	while (envp[i]) {
		now->next = (t_var_lst *)malloc(sizeof(t_var_lst) * 1);
		var_val = ft_slice(envp[i], '=');
		now->next->var = var_val[0];
		now->next->val = var_val[1];
		now->next->next = 0;
		now = now->next;
		i++;
	}
	return head;
}
