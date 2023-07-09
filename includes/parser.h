/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 02:40:22 by asabri            #+#    #+#             */
/*   Updated: 2023/07/06 02:45:09 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H
#include "./minishell.h"
#include "./ft_malloc.h"

#include <stdbool.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct  s_tree
{
    int type;
}        t_tree;

typedef struct s_pipeline
{
    int type;
    t_tree *left;
    t_tree *right;

    
}t_pipeline;
typedef struct s_cmdline
{
    int type;
    t_token *cmd;
    t_token *redir;
}t_cmdline;

#endif