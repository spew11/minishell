#include "minishell.h"

int echo(int argc, char *argv[], t_var_lst *env_lst)
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
			str = ft_getenv(env_lst, argv[i] + 1);
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

int cd(int argc, char *argv[], t_var_lst *env_lst) {
	char *home_path = ft_getenv(env_lst, "HOME");

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

static char **get_var_val(char *str){
	char **strs = ft_slice(str, '=');
	char *var = strs[0];
	char *val = strs[1];

	if (var[0] == 0) { //=happy가 들어온 경우
		return (0);
	}
	if (val[1] == 0) { //happy=가 들어온 경우
		strs[1] = "\"\"";
	}
	int i = 0;
	while (var[i]) {
		if (!ft_isalnum(var[i])) {
			ft_putstr_fd("not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	return (strs);
}

int export(int argc, char *argv[], t_var_lst **export_lst, t_var_lst **env_lst) {
	char **var_val;

	if (argc == 1) {
		print_var_lst(*export_lst);
	}
	else {
		int i = 1;
		while (argv[i]) {
			if (ft_strchr(argv[i], '=')) {
				var_val = get_var_val(argv[i]);
				if (var_val) {
					add_var_lst(export_lst, var_val[0], var_val[1]);
					add_var_lst(env_lst, var_val[0], var_val[1]);
				}
			}
			else {
				int j = 0;
				int err_f = 0;
				while (argv[i][j]) {
					if (!ft_isalnum(argv[i][j])) {
						ft_putstr_fd("not a valid identifier\n", 2);
						err_f = 1;
						break;
					}
					j++;
				}
				if (err_f == 0) {
					add_var_lst(export_lst, argv[i], 0);
				}
			}
			i++;
		}
		sort_var_lst(*export_lst);
	}
	return (0);
}

int unset(int argc, char *argv[], t_var_lst **export_lst, t_var_lst **env_lst) {
	int i = 1;
	while (i < argc) {
		int j = 0;
		int err_f = 0;
		while (argv[i][j]) {
			if (!ft_isalnum(argv[i][j])) {
				ft_putstr_fd("not a valid identifier\n", 2);
				err_f = 1;
				break;
			}
			j++;
		}
		if (err_f == 0) {
			remove_var_lst(export_lst, argv[i]);
			remove_var_lst(env_lst, argv[i]);
		}
		i++;
	}
	return (0);
}

int env(int argc, char *argv[], t_var_lst *env_lst) {
	if (argc != 1) {
		ft_putstr_fd("too many arguments\n", 2);
		return (1);
	}
	print_var_lst(env_lst);
	return (0);
}
