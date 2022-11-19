# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 21:09:19 by eunjilee          #+#    #+#              #
#    Updated: 2022/11/19 16:51:57 by eunjilee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

#CCFLAGS = -Wall -Wextra -Werror

CCFLAGS1 = -L /Users/eunjilee/.brew/opt/readline/lib -lreadline

CCFLAGS2 = -I /Users/eunjilee/.brew/opt/readline/include

MINISHELL = main.c \
			builtins.c \
			utils.c \

SRCS = $(addprefix srcs/, $(MINISHELL))
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

.c.o :
		$(CC) $(CCFLAGS2) -c -o $(<:.c=.o) $<

$(NAME): $(OBJS)
		$(CC) $(CCFLAGS1) -o $(NAME) $(OBJS)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re .c.o
