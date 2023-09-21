# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asabri <asabri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/31 11:03:36 by asabri            #+#    #+#              #
#    Updated: 2023/09/21 05:12:39 by asabri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/env/env.c src/env/env_utils.c src/main.c src/lexer/lexer.c \
	src/lexer/lexer_list.c src/lexer/expand.c src/lexer/lexer_utils.c src/lexer/wildcard.c\
	gc/ft_malloc.c gc/utils_malloc.c src/parser/parser.c \
	src/parser/parser_list.c src/parser/parser_redir.c src/parser/parser_utils.c  \
	src/execution/exec.c src/execution/exec_cmd.c src/execution/exec_pipe.c src/execution/exec_redir.c src/execution/exit_status.c src/built_ins/exit.c\
	src/built_ins/echo.c src/built_ins/env.c \
	src/built_ins/pwd.c src/built_ins/builtins.c src/built_ins/cd.c src/built_ins/export.c src/built_ins/unset.c


CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
READLINE_PATH=$(shell brew --prefix readline)
RM = rm -rf
HEADER = includes/minishell.h includes/ft_malloc.h includes/lexer.h 

OBJS = $(SRC:.c=.o)

all : $(NAME)

libftrule :
	make -C libft-42

%.o : %.c $(HEADER) libft-42/libft.h
		$(CC) $(CFLAGS) -I $(READLINE_PATH)/include -o $@ -c $< 

$(NAME) : $(OBJS) $(HEADER) libftrule
		$(CC) $(CFLAGS) -L $(READLINE_PATH)/lib $(OBJS) libft-42/libft.a -o $@ -lreadline 
clean :
	$(RM) $(OBJS) 
	make clean -C libft-42

fclean : clean
	$(RM) $(NAME) 
	make fclean -C libft-42
	
re : fclean all
