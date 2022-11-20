#include "w_minishell.h"

#define ARGV	11
#define	OPT		12
#define PIPE	13

t_cmd_info	*parse_line(char *line, int *pipe_num)
{
	t_cmd_info	*cmd_arr;
	char		**spl;
	int			flag = 0;

	spl = ft_split(line, ' '); // malloc

	int 	i = 0;
	char	*buff;

	// list생성?
	while (spl[i]) {
		buff = malloc(sizeof(char) * ft_strlen(spl[i])); //malloc
		int spl_i = 0;
		int buf_i = 0;
		while (spl[spl_i]) {
			if (change_flag(spl[spl_i])) {
				//list에 추가
				//buff초기화
			}
			buff[buf_i] = spl[spl_i];
			buf_i++;
			spl_i++;
		}
		//list에 추가
		//buff초기화
	}
	// list -> cmd_info로 바꾸기
}

/*

delim 'white_space', '<', '<<', '>', '>>', '|'

*/
