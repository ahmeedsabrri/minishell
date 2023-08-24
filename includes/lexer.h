/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 02:36:54 by asabri            #+#    #+#             */
/*   Updated: 2023/07/14 08:22:05 by asabri           ###   ########.fr       */
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

// Token types
typedef enum {
    WORD,
    DOUBLE_QUOTE,
    SINGLE_QUOTE,
    REDIRECT_IN,
    REDIRECT_OUT,
    LEFT_PARENTHESIS,
    RIGHT_PARENTHESIS,
    SIGHER,
    EXPANDER,
    END
} t_flag;

typedef struct s_token
{
    char *token;
    t_flag flag;
}t_token;

typedef struct s_cmd{
    char *cmd;
    struct s_token *token;
    struct s_cmd *next;
}t_cmd;
#endif