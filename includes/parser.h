/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 02:40:22 by asabri            #+#    #+#             */
/*   Updated: 2023/09/08 09:16:56 by asabri           ###   ########.fr       */
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

typedef struct s_redir
{
    t_token_type type;
    int file_flages;
    int in_fd;
    char *open_file; 
    struct s_redir *next;
}t_redir;

typedef struct s_pipeline
{
    int type;
    t_tree *left;
    t_tree *right;
}t_pipeline;

typedef struct s_redircmd
{
    int type;
    t_redir *redir_list;
}t_redircmd;

typedef struct s_simplecmd
{
    int type;
    t_token *simplecmd;
    t_redir *redir_list;
}t_simplecmd;


#endif