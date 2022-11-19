# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 21:09:19 by eunjilee          #+#    #+#              #
#    Updated: 2022/11/20 01:32:04 by eunjilee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

#CCFLAGS = -Wall -Wextra -Werror

CCFLAGS = -lreadline -I .

LIBFT_NAME = libft.a
LIBFT_DIR = libft/

MINISHELL = main.c \
			builtins.c \
			utils.c \
			errors.c \

SRCS = $(addprefix srcs/, $(MINISHELL))
OBJS = $(SRCS:%.c=%.o)

LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))

all: $(NAME)

.c.o :
		$(CC) $(CCFLAGS) -c -o $(<:.c=.o) $<

$(LIBFT):
		make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(OBJS) -lreadline -o $(NAME) $(LIBFT)

clean:
		rm -f $(OBJS)
		make -C $(LIBFT_DIR) clean

fclean: clean
		rm -f $(NAME)
		make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re .c.o
