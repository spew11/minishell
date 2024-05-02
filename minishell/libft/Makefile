# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 20:13:44 by eunjilee          #+#    #+#              #
#    Updated: 2022/12/22 17:19:10 by eunjilee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CCFLAGS = -Wall -Wextra -Werror

LIBC = ar rc
LIBR = ranlib

FILES = ft_isprint.c \
		ft_putendl_fd.c \
		ft_strlcat.c \
		ft_substr.c \
		ft_atoi.c \
		ft_itoa.c \
		ft_putnbr_fd.c \
		ft_strlcpy.c \
		ft_tolower.c \
		ft_bzero.c \
		ft_memchr.c \
		ft_putstr_fd.c \
		ft_strlen.c \
		ft_toupper.c \
		ft_calloc.c \
		ft_memcmp.c \
		ft_split.c \
		ft_strmapi.c \
		ft_isalnum.c \
		ft_memcpy.c \
		ft_strchr.c \
		ft_strncmp.c \
		ft_isalpha.c \
		ft_memmove.c \
		ft_strdup.c \
		ft_strnstr.c \
		ft_isascii.c \
		ft_memset.c \
		ft_striteri.c \
		ft_strrchr.c \
		ft_isdigit.c \
		ft_putchar_fd.c \
		ft_strjoin.c \
		ft_strtrim.c

BFILES = ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_lstclear.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstlast.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_lstsize.c

SRCS = $(FILES)
OBJS = $(SRCS:%.c=%.o)

BSRCS = $(BFILES)
BOBJS = $(BSRCS:%.c=%.o)

all: $(NAME)

bonus: all $(BOBJS)
		$(LIBC) $(NAME) $(BOBJS)
		$(LIBR) $(NAME)

.c.o :
		$(CC) $(CCFLAGS) -c -o $(<:.c=.o) $<

$(NAME): $(OBJS)
		$(LIBC) $(NAME) $(OBJS)
		$(LIBR) $(NAME)

clean:
		rm -f $(OBJS) $(BOBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re .c.o bonus

norm:
	norminette $(SRCS) $(BSRCS) *.h
