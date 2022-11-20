#include "minishell.h"

int main(void) {
	char **argv = ft_split("echo $changmo eunji $eui hansu thank $HOME you $ha", ' ');
	int argc = 9;
	echo(argc, argv);
	argv = ft_split("echo -n beautiful $HOME", ' ');
	echo(3, argv);
	return (0);
}

int main(void) {
	cd(2, ft_split("cd ../../", ' '));
	cd(2, ft_split("cd ~", ' '));
	cd(2, ft_split("cd /happy",  ' '));
	cd(2, ft_split("cd ~/wd/42Seoul/42cursus/", ' '));
	cd(1, ft_split("cd", ' '));
	return (0);
}
