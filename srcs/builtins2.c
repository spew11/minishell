/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:06:12 by eunjilee          #+#    #+#             */
/*   Updated: 2022/12/17 17:43:30 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_add_var(char *s, t_var_lst **env_lst, t_var_lst **export_lst)
{
	char	**var_val;

	var_val = ft_slice(s, '=');
	if (var_val)
	{
		if (!var_val[0] || (var_val[0] && chk_var_name(var_val[0])))
		{
			ft_putendl_fd("not a valid identifier", 2);
			return (1);
		}
		if (var_val[1] == 0)
			var_val[1] = ft_strdup("");
		if (!chk_var_name(var_val[0]))
		{
			add_var_lst(export_lst, var_val[0], var_val[1]);
			add_var_lst(env_lst, ft_strdup(var_val[0]), ft_strdup(var_val[1]));
		}
		free(var_val);
		return (0);
	}
	if (!chk_var_name(s))
		add_var_lst(export_lst, ft_strdup(s), 0);
	else
		return (1);
	return (0);
}

int	export(int argc, char *argv[], t_var_lst **env_lst, t_var_lst **export_lst)
{
	int		ret;
	int		i;

	ret = 0;
	if (argc == 1)
		print_var_lst(*export_lst);
	else
	{
		i = 1;
		while (argv[i])
		{
			ret = export_add_var(argv[i], env_lst, export_lst);
			sort_var_lst(*export_lst);
			i++;
		}
	}
	return (ret);
}

int	unset(int argc, char *argv[], t_var_lst **env_lst, t_var_lst **export_lst)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!chk_var_name(argv[i]))
		{
			remove_var_lst(export_lst, argv[i]);
			remove_var_lst(env_lst, argv[i]);
		}
		i++;
	}
	return (0);
}

int	env(int argc, t_var_lst *env_lst)
{
	if (argc != 1)
	{
		ft_putendl_fd("too many arguments", 2);
		return (1);
	}
	print_var_lst(env_lst);
	return (0);
}
