#include "minishell.h"

int echo(int argc, char *argv[])
{
	char *str;
	int opt_f = 0;
	int i = 1;

	if (argc > 1 && ft_strncmp(argv[1], "-n", 2) == 0) {
		opt_f = 1;
		i++;
	}
	while (i < argc) {
		str = argv[i];
		if (ft_strlen(argv[i]) > 1 && argv[i][0] == '$') {
			str = getenv(argv[i] + 1);
			if (str == 0) {
				i++;
				continue;
			}
		}
		printf("%s", str);
		if (i < argc - 1) {
			printf(" ");
		}
		i++;
	}
	if (!opt_f) {
		printf("\n");
	}
	return (0);
}
