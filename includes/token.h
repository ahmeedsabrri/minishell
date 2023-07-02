/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 02:36:54 by asabri            #+#    #+#             */
/*   Updated: 2023/06/29 04:14:29 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
#define TOKEN_H

#include "./minishell.h"
#include "./ft_malloc.h"
typedef struct s_token
{
    char *token;
    char *type;
    bool hd;
    bool  expand;
    struct s_token *next;
    struct s_token *bottom;
}   t_token;

typedef struct s_init
{
    int i;
    bool double_quote;
    bool singl_quote;
    bool space;
    

    int unkown;
    int cp;
    int op;

    
    typedef struct s_token *token;
    typedef struct s_token *bottom;
    
}               t_init;
#endif