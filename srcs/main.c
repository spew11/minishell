#include "minishell.h"

void	get_eof(char *line)
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

void	clear_shell_info(t_shell_info *shell_info)
{
	clear_var_lst(shell_info->externs->env_lst);
	clear_var_lst(shell_info->externs->export_lst);
	free_double_arr(shell_info->externs->env_arr);
	return ;
}

void	init_term(struct termios *term)
{
	tcgetattr(0, term);
	term->c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, term);
	return ;
}

void	init_shell_info(t_shell_info *shell_info, char *envp[])
{
	shell_info->externs = (t_externs *)malloc(sizeof(t_externs) * 1);
	if (!shell_info->externs)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	shell_info->externs->env_lst = init_var_lst(envp);
	shell_info->externs->export_lst = init_var_lst(envp);
	shell_info->externs->env_arr = 0;
	return ;
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
	exit_status = 0;
	init_term(&term);
	init_shell_info(&shell_info, envp);
	signal_on();
	ret = minishell(&shell_info);
	clear_shell_info(&shell_info);
	return (ret);
}
