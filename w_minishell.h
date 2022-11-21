#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <wait.h>
#include "libft.h"

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
} t_cmd_info;

enum	e_opt {
	ARGC,
	REDIR,
};

t_cmd_info	*parse_line(char *line, int *pipe_num, char *envp[]);
//temp
void print(void *ptr);
void	print_cmd_arr(t_cmd_info *cmd_info_arr, int pipe_num);
/*

echo happy > out1 > out2
-> [ { 2, [ "echo", "happy" ], [ {OUTFILE, "out1"}, {OUTFILE, "out2"} ] ]

cat < input | grep "hansu" > out
->	[ 
		[ 1, ["cat"],			[{INFILE, "input"}] ],
		[ 2, ["grap, "hansu"],	[{OUTFILE, "out"}] ],
	]

cat < input | grep hansu | wc -l >> out
->	[
		[ 1, ["cat"],			 [{INFILE, "input"}] ],
		[ 2, ["grep", "hansu"],	 NULL ],
		[ 2, ["wc", "-l"],		 [{FILE_APPEND, "out"}]]
	]

cat < file1 > file2 << eof1 | cat -e >> out 
-> [
		[ 1, ["cat"],		 [{INFILE, "file1"}, {OUTFILE, "file2"}, {HERE_DOC, "eof1"}] ],
		[ 2, ["cat", "-e"],  [{FILE_APPEND, "out"}] ]	
]

*/

// cat -b-n<out<$out -e|cat|cat -e>exp 
// -> [cat, -b-n, <, out, <, $out, -e, |, cat, |, cat, -e, >, exp]