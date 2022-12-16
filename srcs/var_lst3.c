/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_lst3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:07:20 by eunjilee          #+#    #+#             */
/*   Updated: 2022/12/16 16:21:38 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_var_lst(t_var_lst *var_lst)
{
	t_var_lst	*tmp;

	while (var_lst)
	{
		tmp = var_lst;
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
		return (0);
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
