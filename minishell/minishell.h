/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:45:53 by eunjilee          #+#    #+#             */
/*   Updated: 2022/12/22 15:49:50 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
# define INFILE 1
# define HERE_DOC 2
# define OUTFILE 3
# define FILE_APPEND 4

typedef struct s_var_lst
{
	char				*var;
	char				*val;
	struct s_var_lst	*next;
}				t_var_lst;

typedef struct s_redir
{
	int		type;
	char	*str;
}				t_redir;

typedef struct s_externs
{
	t_var_lst	*env_lst;
	t_var_lst	*export_lst;
	char		**env_arr;
}			t_externs;

typedef struct s_shell_info
{
	int			in_fd;
	int			out_fd[2];
	pid_t		*pid_arr;
	t_externs	*externs;
}			t_shell_info;

typedef struct s_cmd_info
{
	int		argc;
	char	**argv;
	int		redir_num;
	t_redir	*redir;
	int		here_num;
	char	**here;
}				t_cmd_info;

enum	e_opt
{
	ARGC,
	REDIR,
};

t_cmd_info	*parse_line(char *line, int *pipe_num, t_var_lst *env_lst);
t_var_lst	*init_var_lst(char *envp[]);
t_var_lst	*copy_lst(t_var_lst *var_lst);
void		here_doc(t_cmd_info *cmd_arr, int pipe_num);
void		print(void *ptr);
void		print_cmd_arr(t_cmd_info *cmd_info_arr, int pipe_num);
extern int	g_exit_status;
void		signal_on(void);
void		chk_fork_err(int pid);
void		chk_fd_err(int fd);
int			ft_execve(char *argv[], t_externs *externs);
void		run_binary(int argc, char *argv[], t_externs *externs);
int			run_cmd(t_cmd_info *cmd_info, t_externs *externs);
int			run_cmds(t_cmd_info *cmd_infos,
				int pipe_num, t_shell_info *shell_info);
int			echo(int argc, char *argv[]);
int			cd(int argc, char *argv[], t_var_lst *env_lst);
void		print_var_lst(t_var_lst *var_lst);
char		**ft_slice(char *str, char sep);
int			export(int argc, char *argv[],
				t_var_lst **env_lst, t_var_lst **export_lst);
void		sort_var_lst(t_var_lst *var_lst);
void		add_var_lst(t_var_lst **var_lst, char *var, char *val);
char		*ft_getenv(t_var_lst *env_lst, char *var);
int			env(int argc, t_var_lst *env_lst);
void		remove_var_lst(t_var_lst **var_lst, char *var);
int			pwd(void);
int			unset(int argc, char *argv[],
				t_var_lst **export_lst, t_var_lst **env_lst);
int			chk_var_name(char *var_name);
void		var_name_err(void);
char		**env_lst2arr(t_var_lst *env_lst);
void		ft_exit(int argc, char *argv[]);
int			is_builtin(char *cmd);
int			exec_builtin(int argc, char *argv[],
				t_var_lst **env_lst, t_var_lst **export_lst);
void		clear_externs(t_externs *externs);
void		clear_var_lst(t_var_lst *var_lst);
void		free_double_arr(char **arr);
void		null_guard_arr(char *arr);
void		null_guard_double_arr(char **arr);
void		init_shell_info(t_shell_info *shell_info, char *envp[]);
void		clear_shell_info(t_shell_info *shell_info);
void		init_term(struct termios *term);
void		wait_pids(pid_t *pid_arr, int pipe_num);
void		unlink_tmpfiles(t_cmd_info *cmd_infos, int pipe_num);
int			ft_access(const char *pathname);
int			pid_err(void);
void		cmd_info_free(t_cmd_info **cmd_info_arr, int pipe_num);
void		null_guard_arr2(int *arr);
#endif
