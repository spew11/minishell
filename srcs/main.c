/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:06:34 by eunjilee          #+#    #+#             */
/*   Updated: 2022/12/16 16:52:57 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_eof(char *line)
{
	if (!line)
	{
		printf("\033[1A");
		printf("\033[11C");
		printf("exit\n");
		exit(0);
	}
	return ;
}

int	minishell(t_shell_info *shell_info)
{
	t_cmd_info	*cmd_infos;
	int			pipe_num;
	char		*line;
	int			ret;

	ret = 0;
	while (1)
	{
		line = readline("minishell$ ");
		get_eof(line);
		add_history(line);
		cmd_infos = parse_line(line, &pipe_num,
				shell_info->externs->env_lst);
		free(line);
		if (cmd_infos)
		{
			ret = run_cmds(cmd_infos, pipe_num, shell_info);
			//free_cmd_infos;
		}
	}
	return (ret);
}

int	main(int argc, char *argv[], char *envp[])
{
	struct termios	term;
	t_shell_info	shell_info;
	int				ret;

	if (argc > 1)
	{
		ft_putendl_fd("too many arguments", 2);
		return (1);
	}
	g_exit_status = 0;
	init_term(&term);
	init_shell_info(&shell_info, envp);
	signal_on();
	ret = minishell(&shell_info);
	clear_shell_info(&shell_info);
	return (ret);
}
