#include "minishell.h"

int find_var_in_lst(t_var_lst *var_lst, char *var) {
	t_var_lst *now;

	now = var_lst;
	while (now) {
		if (ft_strncmp(now->var, var, -1) == 0) {
			return (1);
		}
		now = now->next;
	}
	return (0);
}

char *ft_getenv(t_var_lst *env, char *var) {
	char *val;
	t_var_lst *now;

	now = env;
	while (now) {
		if (ft_strncmp(now->var, var, -1) == 0) {
			return now->val;
		}
		now = now->next;
	}
	return 0;
}
int remove_var_lst(t_var_lst **var_lst, char *var) {
	t_var_lst *now;
	t_var_lst *prev = 0;
	
	if (*var_lst == 0) {
		return 0;
	}
	now = *var_lst;
	if (ft_strncmp(now->var, var, -1) == 0) {
		(*var_lst) = (*var_lst)->next;
		free(now);
		return (0);
	}
	while (now) {
		if (ft_strncmp(now->var, var, -1) == 0) {
			prev->next = now->next;
			free(now);
			return (0);
		}
		prev = now;
		now = now->next;
	}
	return (0);
}

void add_var_lst(t_var_lst **var_lst, char *var, char *val) {
	
	t_var_lst *now;

	if (*var_lst) {
		now = *var_lst;
		while (now->next) {
			if (ft_strncmp(now->var, var, -1) == 0) {
				if (val) {
					now->val = val;
				}
				return ;
			}
			now = now->next;
		}
		if (ft_strncmp(now->var, var, -1) == 0) {
			if (val) {
				now->val = val;
			}
			return ;
		}
		now->next = (t_var_lst *)malloc(sizeof(t_var_lst) * 1);
		now->next->var = var;
		now->next->val = val;
		now->next->next = 0;
	}
	else {
		*var_lst = (t_var_lst *)malloc(sizeof(t_var_lst) * 1);
		(*var_lst)->next->var = var;
		(*var_lst)->next->val = val;
		(*var_lst)->next->next = 0;
	}
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
	if (!var_lst || !find_var_in_lst(var_lst, "PATH")) {
		ft_putstr_fd("No such file or directory\n", 2);
	}
	t_var_lst *now = var_lst;
	while (now) {
		if (now->val) {
			printf("%s", now->var);
			printf("=");
			printf("%s\n", now->val);
		}
		else{
			printf("%s\n", now->var);
		}
		now = now->next;
	}
	return ;
}

t_var_lst *init_var_lst(char *envp[]) {
	int i = 1;
	char **var_val;

	if (!envp || !envp[0]) {
		return 0;
	}
	t_var_lst *head = (t_var_lst *)malloc(sizeof(t_var_lst) * 1);
	var_val = ft_slice(envp[0], '=');
	head->var = var_val[0];
	head->val = var_val[1];
	head->next = 0;
	t_var_lst *now = head;
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
