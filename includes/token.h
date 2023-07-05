/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 02:36:54 by asabri            #+#    #+#             */
/*   Updated: 2023/07/05 21:06:00 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
#define TOKEN_H

#include "./minishell.h"
#include "./ft_malloc.h"

#include <stdbool.h>
typedef enum s_flgs
{
	WORD = 0,
	DQ = 1,
	SQ = 2,
	PIPE = 3,
	RIN = 4,
	ROUT = 5,
	OPAR = 6,
	CPAR = 7,
	SPACE = 8,
	HEREDOC = 11,
	APPEND = 12,
	SUBSHELL,
	REDIR,
	SIGHER,
	END,
}					t_flgs;

typedef struct s_token
{
    char *token;
    
    bool hd;
    bool  expand;
    
    t_flgs type;
    
    struct s_token *next;
    struct s_token *bottom;
    struct s_token *prev;

}               t_token;

typedef struct s_init
{
    int i;
    bool double_quote;
    bool singl_quote;
    bool space;
    

    int unkown;
    int cp;
    int op;

    
    struct s_token *token;
    struct s_token *bottom;
    
}               t_init;
#endif