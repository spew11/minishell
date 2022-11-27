#include "./w_minishell.h"

char **ft_slice(char *str, char sep)
{
	char **strs;
	int i = 0;
	int sep_idx = 0;
	size_t str_len = ft_strlen(str);
	while (str[i]) {
		if (str[i] == sep) {
			sep_idx = i;
			break;
		}
		i++;
	}
	if (i == str_len) {
		return (0);
	}
	strs = (char **)malloc(sizeof(char *) * 3);
	strs[2] = 0;
	strs[0] = (char *)malloc(sizeof(char) * (sep_idx));
	strs[1] = (char *)malloc(sizeof(char) * (str_len - sep_idx + 1));
	ft_strlcpy(strs[0], str, sep_idx + 1);
	ft_strlcpy(strs[1], str + sep_idx + 1, str_len - sep_idx);
	return (strs);
}

t_var_lst *init_var_lst(char *envp[])
{
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