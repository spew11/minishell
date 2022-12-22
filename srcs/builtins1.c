/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:06:05 by eunjilee          #+#    #+#             */
/*   Updated: 2022/12/22 15:33:35 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_err(char *str, int ret)
{
	ft_putendl_fd(str, 2);
	exit(ret);
	return ;
}

void	ft_exit(int argc, char *argv[])
{
	int	i;
	int	argv_f;

	argv_f = 1;
	ft_putendl_fd("exit", 1);
	if (argc == 1)
		exit(0);
	i = -1;
	while (argv[1][++i])
	{
		if (!ft_isdigit(argv[1][i]))
		{
			argv_f = 0;
			break ;
		}
	}
	if (argv_f)
	{
		if (argc == 2)
			exit(ft_atoi(argv[1]));
		else
			exit_err("too many arguments", 1);
	}
	exit_err("numieric argument required", 255);
	return ;
}

static void	echo_opt(char *argv[], int *i, int *opt_f, int b_flag)
{
	int	j;

	while (argv[++(*i)])
	{
		if (argv[*i][0] != '-')
			break ;
		else
		{
			b_flag = 0;
			j = 0;
			while (argv[*i][++j])
			{
				if (argv[*i][j] != 'n')
				{
					b_flag = 1;
					break ;
				}
			}
			if (b_flag == 1)
				break ;
			*opt_f = 1;
		}
		if (b_flag == 1)
			break ;
	}
}

int	echo(int argc, char *argv[])
{
	int	opt_f;
	int	i;

	opt_f = 0;
	i = 0;
	echo_opt(argv, &i, &opt_f, 0);
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i < argc - 1)
			printf(" ");
		i++;
	}
	if (!opt_f)
		printf("\n");
	return (0);
}
