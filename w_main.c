#include "w_minishell.h"

// void cmd_redir(t_redir *redir);

// void	recur(t_cmd_info *cmd_arr, char *envp[], int pipe_num, int cmd_idx, int pre_pipe)
// {
// 	int	pipefd[2];
// 	int pid;
	
// 	// 마지막 cmd를 제외한 상황
// 	if (cmd_idx < pipe_num) {

// 		pipe(pipefd);
// 		pid = fork();
// 		if (pid == 0) {
// 			if (cmd_idx != 0) {
// 				dup2(pre_pipe, 0);
// 				close(pre_pipe);
// 			}
// 			dup2(pipefd[1], 1);
// 			close(pipefd[1]);
// 			cmd_redir(cmd_arr[cmd_idx].redir);
// 			execve("filepath", cmd_arr[cmd_idx].argv, envp);
// 		}
// 		if (pre_pipe != (-1))
// 			close(pre_pipe);
// 		close(pipefd[1]);
// 		recur(cmd_arr, envp, pipe_num, cmd_idx + 1, pipefd[0]);
// 	}
// 	// 파이프를 만들었을때 마지막 cmd 실행하는 상황
// 	else if (pipe_num > 0) {
// 		pid = fork();
// 		if (pid == 0) {
// 			dup2(pre_pipe, 0);
// 			close(pre_pipe);
// 			cmd_redir(cmd_arr[cmd_idx].redir);
// 			execve("filepath", cmd_arr[cmd_idx].argv, envp);
// 		}
// 		close(pre_pipe);
// 	}
// 	// 파이프를 만들지 않았을때 cmd 실행하는 상황
// 	else {
// 		cmd_redir(cmd_arr[cmd_idx].redir);
// 		execve("filepath", cmd_arr[cmd_idx].argv, envp);
// 	}
// }


// cat -e < infile << infile2 > outfile | cat -e >> outfile2



int main(int argc, char *argv[], char *envp[])
{
	char		*line;
	int			pipe_num;
	t_cmd_info	*cmd_arr;

	line = readline("minishell$ ");

	cmd_arr = parse_line(line, &pipe_num, envp);
	// recur(cmd_arr, envp, pipe_num, 0, -1);
}