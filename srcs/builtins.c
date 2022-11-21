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

int cd(int argc, char *argv[]) {
	char *home_path = getenv("HOME");

	if (argc > 2) {
		ft_putstr_fd("too many arguments\n", 2);
		return (1);
	}
	if (argc == 1) {
		chdir(home_path);
	}
	else {
		char **paths = ft_split(argv[1], '/');
		int i = 0;
		while (paths[i]) {
			if (ft_strlen(paths[i]) == 1 && paths[i][0] == '~') {
				chdir(home_path);
			}
			else {
				if (ft_access(paths[i]) < 0) {
					ft_putstr_fd("No such file or directory\n", 2);
					return (1);
				}
				chdir(paths[i]);
			}
			i++;
		}
	}
	return (0);
}

int pwd(void) {
	//linux path maximum length is 4096
	char buf[4096];
	getcwd(buf, 4096);
	printf("%s\n", buf);
	return (0);
}

/*int export(int argc, char *argv[], t_export_lst *export_lst) {
	if (argc == 
	return (0);
}*/
