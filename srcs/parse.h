#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include "./libft.h"

#define INFILE		1 // '<'
#define	HERE_DOC	2 // '<<'
#define OUTFILE		3 // '>'
#define FILE_APPEND 4 // '>>'

typedef struct s_redir {
	int		type;
	char	*str;
} t_redir;

typedef struct s_cmd_info {
	int		argc;
	char	**argv;
	int		redir_num;
	t_redir *redir;
	int		here_num;
	char	**here;
} t_cmd_info;

typedef struct s_var_lst {
	char *var;
	char *val;
	struct s_var_lst *next;
}				t_var_lst;

enum	e_opt {
	ARGC,
	REDIR,
	HERE,
};

enum	e_idx {
	AV = 0,
	RE = 1,
	CMD = 3,
};

enum	e_err {
	SYS = -1,
	NONE = 0,
	SYN = 1,
};

extern int	g_exit_status;

t_list	*divide_line_into_token(char *line, int *pipe_num);
t_cmd_info	*init_cmd_info_arr(t_list *token_list, int pipe_num, \
			t_list **here_list, int *syntax_err);
t_list	*here_doc(t_cmd_info *cmd_arr, int pipe_num, t_list *here_list, int *err);
int	fill_cmd_info_arr(t_cmd_info *cmd_info_arr, t_list *cur_token, \
		t_list *cur_tmp, t_var_lst *env_lst);
t_list	*split_by_space(char *line);
void	cmd_info_free(t_cmd_info **cmd_info_arr, int pipe_num);
int		init_cmd_info(t_cmd_info **cmd_info, int cmd_i, int *cnt);
int		malloc_cmd_info_arr(t_cmd_info **cmd_info_arr, t_list *cur, \
			t_list **here_list, char **err_str);
void	tmp_clear(t_list **tmp_list);
int		is_pipe(char *token);
int		is_redir(char *str);
int		is_here(char *token);
int		is_quote(char ch);
int		is_env(int quote, char ch);
void	ft_free(void *ptr);
int		buff_free(char *buff);
int		buff_to_list(char *buff, int *buf_i, t_list **list);
int		get_redir(t_cmd_info *cmd_info_arr, t_list *cur_token, \
			int *idx, t_var_lst *env_lst);
int		get_here_doc(t_cmd_info *cmd_info_arr, t_list *cur_token, \
			int *idx, t_list **cur_tmp);
int		get_type(char *str);
int		get_text_list(t_list **text_list, char *buff, char *str, t_var_lst *env_lst);
char	*replace_symbol_to_text(char *str, t_var_lst *env_lst, int *err);

// temp
void	print(void *ptr);
void	print_cmd_arr(t_cmd_info *cmd_info_arr, int pipe_num);
