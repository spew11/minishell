#include "w_minishell.h"

#define ARGV	11
#define	OPT		12
#define PIPE	13

char *convert_envp();

int	is_flag(char *buff)
{
	if (!ft_strncmp(buff, "<", 2))
		return (1);
	if (!ft_strncmp(buff, "<<", 3))
		return (1);
	if (!ft_strncmp(buff, ">", 2))
		return (1);
	if (!ft_strncmp(buff, ">>", 3))
		return (1);
	if (!ft_strncmp(buff, "|", 2))
		return (1);
	return (0);
}

int	is_new_element(char *str, int jdx, char *buff)
{
	// flag를 버퍼에 넣는 상황
	if (str[jdx] == '|')
		return (1);
	else if (str[jdx] == '<') {
		if (!ft_strncmp(buff, "<", 2))
			return (0);
		return (1);
	}
	else if (str[jdx] == '>') {
		if (!ft_strncmp(buff, ">", 2))
			return (0);
		return (1);
	}
	// flag가 아닌 일반 문자일때 buff가 flag이면 새로 담아야한다.
	if (is_flag(buff))
		return (1);
	return (0);
}

t_list *get_element_list(char *line, char *envp[])
{
	t_list	*el_list;
	char	**spl;
	char	*buff;
	int 	spl_i = 0;
	int		spl_j = 0;
	int		buf_i = 0;

	spl = ft_split(line, ' '); // malloc
	while (spl[spl_i]) {
		buff = malloc(sizeof(char) * (ft_strlen(spl[spl_i]) + 1)); // malloc
		ft_bzero(buff, ft_strlen(spl[spl_i]) + 1);
		spl_j = 0;
		buf_i = 0;
		while (spl[spl_i][spl_j]) {
			if (ft_strncmp(buff, "", 1) && is_new_element(spl[spl_i], spl_j, buff)) {
				buff[buf_i] = '\0';
				ft_lstadd_back(&el_list, ft_lstnew(ft_strdup(buff)));
				ft_bzero(buff, ft_strlen(buff));
				buf_i = 0;
			}
			buff[buf_i] = spl[spl_i][spl_j];
			buf_i++;
			spl_j++;
		}
		buff[buf_i] = '\0';
		ft_lstadd_back(&el_list, ft_lstnew(ft_strdup(buff)));
		free(buff);
		spl_i++;
	}
	return (el_list);
}

t_cmd_info	*parse_line(char *line, int *pipe_num, char *envp[])
{
	t_cmd_info	*cmd_arr;
	t_list		*el_list;

	// 역할에 구분없이 그냥 쪼개서 리스트에 담는다.
	// cat -b-n<out<$out -e|cat|cat -e>exp 
	// -> [cat, -b-n, <out, <$out, -e, |, cat, |, cat, -e, >exp]
	el_list = get_element_list(line, envp);
	ft_lstiter(el_list, print);printf("\n");
	return (NULL);
	// list -> cmd_info로 바꾸기
}

/*

delim 'white_space', '<', '<<', '>', '>>', '|', '-'

*/
