/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 02:36:54 by asabri            #+#    #+#             */
/*   Updated: 2023/08/29 11:14:34 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#include "./minishell.h"
#include "./ft_malloc.h"

#include <stdbool.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum e_token_type{
	WORD,
	PIPE,
}			t_token_type;
typedef struct s_init
{
	int dq;
	int sq;
	int h;
	int op;
	int cp;
	int space;
	int i;
	struct s_token	*token;
}t_init;
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}				t_token;

t_token	*ft_lexer(char *line);
t_token *ft_lastlst(t_token *node);
void add_back(t_token **lst,t_token *new);
t_token *newtoken(char *token);
char *get_word(char *str, int *index);
char *get_q(char *str,char c,int *index);
#endif