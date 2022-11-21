#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
//# include <sys/fcntl.h>
# include "libft/libft.h"
# define FILE 1 //> , <
# define PIPE 2 // |
# define HERE_DOC 3 // <<
# define FILE_END 4 // >>
# define STDOUT 5

int exit_status;

typedef struct s_var_lst {
	char *var;
	char *val;
	struct s_var_lst *next;
}				t_var_lst;

typedef struct s_cmd_info {
	char	**argv;
	int		argc;
	int		in_type;
	char	*in_str;
	int		out_type;
	char	*out_str;
}				t_cmd_info;


void	sig_handler(int signal);
void	signal_on(void);

void		chk_fork_err(int pid);
void		chk_fd_err(int fd);

void ft_execve(char *argv[], char *envp[]);
int	ft_access(const char *pathname);
int	run_cmds(t_cmd_info **cmd_infos, char *envp[]);

int echo(int argc, char *argv[], t_var_lst *env_lst);
int cd(int argc, char *argv[], t_var_lst *env_lst);
//int init_var_lst(t_var_lst *var_lst, char *envp[]);
t_var_lst *init_var_lst(char *envp[]);
void print_var_lst(t_var_lst *var_lst);
char **ft_slice(char *str, char sep);
int export(int argc, char *argv[], t_var_lst *export_lst, t_var_lst *env_lst);
void sort_var_lst(t_var_lst *var_lst);
void add_var_lst(t_var_lst *var_lst, char *var, char *val);
char *ft_getenv(t_var_lst *env_lst, char *var);
int env(int argc, char *argv[], t_var_lst *env_lst);
int remove_var_lst(t_var_lst *var_lst, char *var);
int unset(int argc, char *argv[], t_var_lst *export_lst, t_var_lst *env_lst);
#endif
