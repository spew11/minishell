# MINISHELL
This repository has a program that provides essential features of the Bash shell called MINISHELL.
## Feafures
- Minishell executes excutables based on absolute or relative paths, as well as the PATH variable.
- Have a working history.
- Interprocess communication (IPC) is possible through redirections and pipes.
- it enables the management of environment variables.
- "$?" contains the exit status of the most recently executed foreground pipeline,
- the functionalities of e ctrl-C, ctrl-D, and ctrl-\ are the same as in Bash.
- it includes the following built-in functions.  
    -  echo with option -n
    -  cd with only a relative or absolute path
    -  pwd with no options
    -  export with no options
    -  unset with no options
    -  env with no options or arguments
    -  exit with no options

> This project is developed through C language in mac

## Running this program locally
```bash
git https://github.com/spew11/minishell.git && \
  make
``` 
--------------------
