# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/25 23:28:39 by hben-bou          #+#    #+#              #
#    Updated: 2023/08/02 02:10:09 by hben-bou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I/Users/hben-bou/homebrew/opt/readline/include #-g -fsanitize=address

SRC = implement.c utils.c ft_split.c environment.c path.c parcing.c heredoc.c create_files.c old_pwd.c builtins.c echo.c spliting.c redirections1.c ft_atoi.c pipes.c
		
OBJ = implement.o utils.o ft_split.o environment.o path.o parcing.o heredoc.o create_files.o old_pwd.o builtins.o echo.o spliting.o redirections1.o ft_atoi.o pipes.o

all: mandatory
mandatory: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SRC) -L/Users/hben-bou/homebrew/opt/readline/lib -lreadline  -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

