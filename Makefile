# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asabri <asabri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/31 11:03:36 by asabri            #+#    #+#              #
#    Updated: 2023/05/31 18:58:24 by asabri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/env/env.c src/env/env_utils.c src/main.c src/token/tokenizing.c

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf
HEADER = includes/minishell.h   

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