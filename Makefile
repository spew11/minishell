# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eunjilee <eunjilee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/18 23:15:09 by eunjilee          #+#    #+#              #
#    Updated: 2023/12/09 14:41:11 by eunjilee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: build run

build:
	@docker build -t minishell:latest .

run: clean
	@docker run -it --name minishell-container minishell:latest

clean:
	@if [ "$(shell docker ps -aq -f name=minishell-container)" ]; then \
		docker rm minishell-container; \
	fi

fclean: clean
	@if [ "$(shell docker images -q minishell:latest)" ]; then \
		docker rmi -f minishell:latest; \
	fi

re: fclean all

.PHONY: all build run clean fclean re
