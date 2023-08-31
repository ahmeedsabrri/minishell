/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 02:36:54 by asabri            #+#    #+#             */
/*   Updated: 2023/08/31 05:53:14 by asabri           ###   ########.fr       */
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
	END,
}			t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}				t_token;

typedef struct s_init
{
	int dq;
	int sq;
	int h;
	int rin;
	int rout;
	int apand;
	int space;
	int i;
	struct s_token	*token;
}t_init;

#endif