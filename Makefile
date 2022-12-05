# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_in_mac                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 21:09:19 by eunjilee          #+#    #+#              #
#    Updated: 2022/12/05 16:23:22 by eunjilee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc -I .

CCFLAGS = -Wall -Wextra -Werror

CCFLAGS1 = -L /Users/eunjilee/.brew/opt/readline/lib -lreadline

CCFLAGS2 = -I /Users/eunjilee/.brew/opt/readline/include

LIBFT_NAME = libft.a
LIBFT_DIR = libft/

MINISHELL = main.c \
			builtins.c \
			utils.c \
			env.c \
			parse_line.c \
			w_utils.c \
			run_cmds.c \
			div_line.c\
			fill_cmd_info.c\
			init_cmd_info.c\
			heredoc.c

SRCS = $(addprefix srcs/, $(MINISHELL))
OBJS = $(SRCS:%.c=%.o)

LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))

all: $(NAME)

.c.o :
		$(CC) $(CCFLAGS2) -c -o $(<:.c=.o) $<

$(LIBFT):
		make -C $(LIBFT_DIR) bonus

$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(CCFLAGS1) -o $(NAME) $(OBJS) $(LIBFT)

clean:
		rm -f $(OBJS)
		make -C $(LIBFT_DIR) clean

fclean: clean
		rm -f $(NAME)
		make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re .c.o
