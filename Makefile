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
	docker build -t minishell:latest ./minishell

run:
	docker run -it --name minishell-container minishell:latest sh


clean:
	docker rm minishell-container
	docker rmi -f minishell:latest

re: clean all

.PHONY: all run build clean re
