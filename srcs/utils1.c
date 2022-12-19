/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:06:55 by eunjilee          #+#    #+#             */
/*   Updated: 2022/12/17 17:51:38 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chk_var_name(char *var_name)
{
	int	i;

	i = 0;
	while (var_name[i])
	{
		if (i == 0 && ft_isdigit(var_name[i]))
		{
			ft_putendl_fd("not a valid identifier", 2);
			return (1);
		}
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
		{
			ft_putendl_fd("not a valid identifier", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**ft_slice(char *str, char sep)
{
	char	**strs;
	size_t	sep_idx;
	size_t	str_len;

	str_len = ft_strlen(str);
	sep_idx = 0;
	while (str[sep_idx] && str[sep_idx] != sep)
		sep_idx++;
	if (sep_idx == str_len)
		return (0);
	strs = (char **)calloc(3, sizeof(char *));
	null_guard_double_arr(strs);
	if (sep_idx != 0)
	{
		strs[0] = (char *)malloc(sizeof(char) * (sep_idx + 1));
		null_guard_arr(strs[0]);
		ft_strlcpy(strs[0], str, sep_idx + 1);
	}
	if (sep_idx != str_len - 1)
	{
		strs[1] = (char *)malloc(sizeof(char) * (str_len - sep_idx));
		null_guard_arr(strs[1]);
		ft_strlcpy(strs[1], str + sep_idx + 1, str_len - sep_idx);
	}
	return (strs);
}

void	sig_handler(int sig_t)
{
	pid_t	pid;
	int		status;

	if (sig_t == SIGINT)
	{
		pid = waitpid(-1, &status, WNOHANG);
		if (pid == -1)
		{
			printf("\n");
			if (rl_on_new_line() == -1)
				exit(1);
			rl_replace_line("", 1);
			rl_redisplay();
			g_exit_status = 1;
		}
		else
		{
			printf("\n");
		}
	}
	return ;
}

void	signal_on(void)
{
	signal(SIGINT, (void *)sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
