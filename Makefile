# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_in_mac                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 21:09:19 by eunjilee          #+#    #+#              #
#    Updated: 2022/12/22 15:49:39 by eunjilee         ###   ########.fr        #
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
			builtins1.c \
			builtins2.c \
			builtins3.c \
			utils1.c \
			utils2.c \
			utils3.c \
			utils4.c \
			init_and_clear.c \
			var_lst1.c \
			var_lst2.c \
			var_lst3.c \
			run_cmds1.c \
			run_cmds2.c \
			run_cmds3.c \
			parse_line.c \
			divide_line.c\
			init_cmd_info.c \
			fill_cmd_info.c \
			heredoc.c \
			get_redir.c \
			get_text_list.c \
			init_cmd_info_arr.c \
			is_redir.c \
			malloc_cmd_info_arr.c \
			parse_free.c \
			parse_utils.c \
			split_by_space.c \
			symbol_to_text.c \
			tmp_err.c \

SRCS = $(addprefix srcs/, $(MINISHELL))
OBJS = $(SRCS:%.c=%.o)

LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))

all: $(NAME)

.c.o :
		$(CC) $(CCFLAGS) $(CCFLAGS2) -c -o $(<:.c=.o) $<

$(LIBFT):
		make -C $(LIBFT_DIR) bonus

$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(CCFLAGS) $(CCFLAGS1) -o $(NAME) $(OBJS) $(LIBFT)

clean:
		rm -f $(OBJS)
		make -C $(LIBFT_DIR) clean

fclean: clean
		rm -f $(NAME)
		make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re .c.o
