/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_lst1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:07:12 by eunjilee          #+#    #+#             */
/*   Updated: 2022/12/16 16:07:13 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_lst(t_var_lst *seat, t_var_lst *min)
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

static void	init_var_lst_in_mid(char *envp[], t_var_lst *head)
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
