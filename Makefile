# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asabri <asabri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/31 11:03:36 by asabri            #+#    #+#              #
#    Updated: 2023/09/01 01:29:00 by asabri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/env/env.c src/env/env_utils.c src/main.c src/lexer/lexer.c \
	src/lexer/lexer_list.c src/lexer/expand.c src/lexer/lexer_utils.c \
	gc/ft_malloc.c gc/utils_malloc.c src/parser/parser.c \
	src/parser/parser_list.c src/parser/parser_utils.c


CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

RM = rm -rf
HEADER = includes/minishell.h includes/ft_malloc.h includes/lexer.h 

OBJS = $(SRC:.c=.o)

all : $(NAME)

libftrule :
	make -C libft-42

%.o : %.c $(HEADER) libft-42/libft.h
		$(CC) $(CFLAGS) -o $@ -c $<

$(NAME) : $(OBJS) $(HEADER) libftrule
		$(CC) $(CFLAGS) $(OBJS) libft-42/libft.a -o $@ -lreadline
clean :
	$(RM) $(OBJS) 
	make clean -C libft-42

fclean : clean
	$(RM) $(NAME) 
	make fclean -C libft-42
	
re : fclean all
credit:
	@echo "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
	@echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
	@echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"