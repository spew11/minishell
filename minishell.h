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

typedef struct s_env_lst {
	char **env_val;
	struct s_env_lst *next;
}				t_env_lst;

typedef struct s_cmd_info {
	t_env_lst *env_lst;
	t_env_lst *export_lst;
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

int echo(int argc, char *argv[]);
int cd(int argc, char *argv[]);
int init_env_lst(t_env_lst *env_lst, char *envp[]);
char **ft_slice(char *str, char sep);
#endif
