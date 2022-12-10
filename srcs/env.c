#include "minishell.h"

void	clear_var_lst(t_var_lst *var_lst)
{
	while (var_lst)
	{
		t_var_lst *tmp = var_lst;
		var_lst = var_lst->next;
		free(tmp->var);
		free(tmp->val);
		free(tmp);
	}
	return ;
}

int	get_cnt_lst(t_var_lst *var_lst)
{
	int	cnt;

	cnt = 0;
	while (var_lst)
	{
		var_lst = var_lst->next;
		cnt++;
	}
	return (cnt);
}

char	**env_lst2arr(t_var_lst *env_lst)
{
	char	**env_arr;
	char	*tmp;
	int		i;

	if (!env_lst)
		return 0;
	env_arr = (char **)malloc(sizeof(char *) * (get_cnt_lst(env_lst) + 1));
	null_guard_double_arr(env_arr);
	i = 0;
	while (env_lst)
	{
		if (env_lst->val)
		{
			tmp = ft_strjoin(env_lst->var, "=");
			env_arr[i] = ft_strjoin(tmp, env_lst->val);
			free(tmp);
		}
		else
			env_arr[i] = env_lst->var;
		i++;
		env_lst = env_lst->next;
	}
	env_arr[i] = 0;
	return (env_arr);
}

int	find_var_in_lst(t_var_lst *var_lst, char *var)
{
	while (var_lst)
	{
		if (ft_strncmp(var_lst->var, var, -1) == 0)
		{
			return (1);
		}
		var_lst = var_lst->next;
	}
	return (0);
}

char	*ft_getenv(t_var_lst *env, char *var)
{
	while (env)
	{
		if (ft_strncmp(env->var, var, -1) == 0)
		{
			return env->val;
		}
		env = env->next;
	}
	return (0);
}

void	remove_mid_lst(t_var_lst **var_lst, char *var)
{
	t_var_lst	*prev;
	t_var_lst	*now;

	now = *var_lst;
	while (now)
	{
		if (ft_strncmp(now->var, var, -1) == 0)
		{
			prev->next = now->next;
			free(now->var);
			free(now->val);
			free(now);
			return ;
		}
		prev = now;
		now = now->next;
	}
	return ;
}

void	remove_var_lst(t_var_lst **var_lst, char *var)
{
	t_var_lst	*prev;
	
	if (!(*var_lst))
		return ;
	prev = *var_lst;
	if (ft_strncmp(prev->var, var, -1) == 0)
	{
		(*var_lst) = (*var_lst)->next;
		free(prev->var);
		free(prev->val);
		free(prev);
		return ;
	}
	remove_mid_lst(var_lst, var);
	return ;
}

void	add_var_lst_1(t_var_lst **var_lst, char *var, char *val, t_var_lst *now)
{
	now = *var_lst;
	while (now->next)
	{
		if (ft_strncmp(now->var, var, -1) == 0)
		{
			if (val)
				now->val = val;
			return ;
		}
		now = now->next;
	}
	if (ft_strncmp(now->var, var, -1) == 0)
	{
		if (val)
			now->val = val;
		return ;
	}
	now->next = (t_var_lst *)malloc(sizeof(t_var_lst) * 1);
	now->next->var = var;
	now->next->val = val;
	now->next->next = 0;
	return ;
}

void	add_var_lst(t_var_lst **var_lst, char *var, char *val)
{
	t_var_lst	*now;

	if (*var_lst)
	{
		add_var_lst_1(var_lst, var, val, now);
	}
	else
	{
		*var_lst = (t_var_lst *)malloc(sizeof(t_var_lst) * 1);
		(*var_lst)->next->var = var;
		(*var_lst)->next->val = val;
		(*var_lst)->next->next = 0;
	}
	return ;
}

void	swap_lst(t_var_lst *seat, t_var_lst *min)
{
	char	*var_tmp;
	char	*val_tmp;

	var_tmp = seat->var;
	val_tmp = seat->val;
	seat->var = min->var;
	seat->val = min->val;
	min->var = var_tmp;
	min->val = val_tmp;
	return ;
}

void	sort_var_lst(t_var_lst *var_lst)
{
	t_var_lst	*seat;
	t_var_lst	*ptr;
	t_var_lst	*min;

	seat = var_lst;
	while (seat->next)
	{
		min = seat;
		ptr = seat->next;
		while (ptr)
		{
			if (ft_strncmp(min->var, ptr->var, -1) > 0)
				min = ptr;
			ptr = ptr->next;
		}
		if (ft_strncmp(seat->var, min->var, -1))
			swap_lst(seat, min);
		seat = seat->next;
	}
	return ;
}

void	print_var_lst(t_var_lst *var_lst)
{
	t_var_lst	*now;

	now = var_lst;
	while (now)
	{
		if (now->val)
		{
			printf("%s", now->var);
			printf("=");
			printf("%s\n", now->val);
		}
		else
		{
			printf("%s\n", now->var);
		}
		now = now->next;
	}
	return ;
}

void	init_var_lst_in_mid(char *envp[], t_var_lst *head)
{
	char		**var_val;
	t_var_lst	*now;
	int			i;

	now = head;
	i = 1;
	while (envp[i])
	{
		now->next = (t_var_lst *)malloc(sizeof(t_var_lst) * 1);
		if (!(now->next))
		{
			ft_putendl_fd(strerror(errno), 2);
			exit (1);
		}
		var_val = ft_slice(envp[i], '=');
		now->next->var = var_val[0];
		now->next->val = var_val[1];
		now->next->next = 0;
		free(var_val);
		now = now->next;
		i++;
	}
	return ;
}

t_var_lst	*init_var_lst(char *envp[])
{
	char		**var_val;
	t_var_lst	*head;

	if (!envp || !envp[0])
		return (0);
	head = (t_var_lst *)malloc(sizeof(t_var_lst) * 1);
	if (!head)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	var_val = ft_slice(envp[0], '=');
	head->var = var_val[0];
	head->val = var_val[1];
	head->next = 0;
	free(var_val);
	init_var_lst_in_mid(envp, head);
	return (head);
}
