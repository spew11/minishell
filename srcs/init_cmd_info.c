#include "./parse.h"

static int	init_cmd_argv(t_cmd_info *cmd_info, int *cnt)
{
	int	i;

	i = 0;
	cmd_info->argc = cnt[ARGC];
	cmd_info->argv = malloc(sizeof(char *) * (cnt[ARGC] + 1));
	if (!cmd_info->argv)
		return (0);
	i = 0;
	while (i < cnt[ARGC] + 1)
	{
		cmd_info->argv[i] = NULL;
		i++;
	}
	return (1);
}

static int	init_cmd_redir(t_cmd_info *cmd_info, int *cnt)
{
	int	i;

	i = 0;
	cmd_info->redir_num = cnt[REDIR];
	cmd_info->redir = malloc(sizeof(t_redir) * (cnt[REDIR] + 1));
	if (!cmd_info->redir)
		return (0);
	i = 0;
	while (i < cnt[REDIR] + 1)
	{
		cmd_info->redir[i].type = 0;
		cmd_info->redir[i].str = NULL;
		i++;
	}
	return (1);
}

static int	init_cmd_here(t_cmd_info *cmd_info, int *cnt)
{
	int	i;

	i = 0;
	cmd_info->here_num = cnt[HERE];
	cmd_info->here = malloc(sizeof(char *) * (cnt[HERE] + 1));
	if (!cmd_info->here)
		return (0);
	i = 0;
	while (i < cnt[HERE] + 1)
	{
		cmd_info->here[i] = NULL;
		i++;
	}
	return (1);
}

int	init_cmd_info(t_cmd_info **cmd_info, int cmd_i, int *cnt)
{
	if (!init_cmd_argv((*cmd_info + cmd_i), cnt) || \
		!init_cmd_redir((*cmd_info + cmd_i), cnt) || \
		!init_cmd_here((*cmd_info + cmd_i), cnt))
		return (0);
	cnt[ARGC] = 0;
	cnt[REDIR] = 0;
	cnt[HERE] = 0;
	return (1);
}