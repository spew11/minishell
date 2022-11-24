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
# include "libft/libft.h"
# define INFILE 1 // '<'
# define HERE_DOC 2 // '<<'
# define OUTFILE 3 // '>'
# define FILE_APPEND 4 // '>>'

typedef struct s_redir {
	int		type;
	char	*str;
} t_redir;

typedef struct s_cmd_info {
	int		argc;
	char	**argv;
	int		redir_num;
	t_redir *redir;
	char **tmpfiles;
} t_cmd_info;

enum	e_opt {
	ARGC,
	REDIR,
};

t_cmd_info	*parse_line(char *line, int *pipe_num, char *envp[]);
//temp
void print(void *ptr);
void	print_cmd_arr(t_cmd_info *cmd_info_arr, int pipe_num);

int exit_status;

typedef struct s_var_lst {
	char *var;
	char *val;
	struct s_var_lst *next;
}				t_var_lst;

void	sig_handler(int signal);
void	signal_on(void);

void		chk_fork_err(int pid);
void		chk_fd_err(int fd);

void ft_execve(char *argv[], t_var_lst *env_lst);
int	ft_access(const char *pathname);
int	run_cmds(t_cmd_info *cmd_infos, int pipe_num, t_var_lst *env_lst);

int echo(int argc, char *argv[], t_var_lst *env_lst);
int cd(int argc, char *argv[], t_var_lst *env_lst);
t_var_lst *init_var_lst(char *envp[]);
void print_var_lst(t_var_lst *var_lst);
char **ft_slice(char *str, char sep);
int export(int argc, char *argv[], t_var_lst **export_lst, t_var_lst **env_lst);
void sort_var_lst(t_var_lst *var_lst);
void add_var_lst(t_var_lst **var_lst, char *var, char *val);
char *ft_getenv(t_var_lst *env_lst, char *var);
int env(int argc, char *argv[], t_var_lst *env_lst);
int remove_var_lst(t_var_lst **var_lst, char *var);
int unset(int argc, char *argv[], t_var_lst **export_lst, t_var_lst **env_lst);
int chk_var_name(char *var_name);
void var_name_err(void);
char **env_lst2env_arr(t_var_lst *env_lst);
#endif
