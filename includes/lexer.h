/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 02:36:54 by asabri            #+#    #+#             */
/*   Updated: 2023/09/19 20:56:34 by asabri           ###   ########.fr       */
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
	HEREDOC,
	APPEND,
	RIN,
	ROUT,
	QOUTE,
	NOT_QOUTE,
	SIGNAL,
	REDIRECTION,
	WILDCARD,
	END,
}			t_token_type;

typedef struct s_token
{
	t_token_type	type;
	t_token_type	is_qoute;
	char			*value;
	int herdoc;
	struct s_token	*next;
}				t_token;

typedef struct s_init
{
	int dq;
	int sq;
	int h;
	int space;
	int i;
	struct s_token	*token;
}t_init;

#endif