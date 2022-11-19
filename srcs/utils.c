#include "minishell.h"

void sig_handler(int signal) {
	if (signal == SIGINT) {
		printf("\n");
	}
	if (rl_on_new_line() == -1) {
		exit(1);
	}
	rl_replace_line("", 1);
	rl_redisplay();
}

void signal_on() {
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
