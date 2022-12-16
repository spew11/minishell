/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_lst2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:07:16 by eunjilee          #+#    #+#             */
/*   Updated: 2022/12/16 16:20:54 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_var_lst *env, char *var)
{
	while (env)
	{
		if (ft_strncmp(env->var, var, -1) == 0)
		{
			return (env->val);
		}
		env = env->next;
	}
	return (0);
}

static void	remove_mid_lst(t_var_lst **var_lst, char *var)
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
			if (now->val)
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
		if (prev->val)
			free(prev->val);
		free(prev);
		return ;
	}
	remove_mid_lst(var_lst, var);
	return ;
}

static void	add_var_lst_1(t_var_lst **var_lst,
		char *var, char *val, t_var_lst *now)
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
