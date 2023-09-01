/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 02:40:22 by asabri            #+#    #+#             */
/*   Updated: 2023/09/01 01:25:03 by asabri           ###   ########.fr       */
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

typedef struct s_simplecmd
{
    int type;
    t_token *simplecmd;
    t_redir *redir_list;
    
}t_simplecmd;
t_tree *parser(t_token *tokens);
t_tree *parse_pipe(t_token **tokens);
t_tree *parse_cmd(t_token **tokens);
int ft_herdoc(char *delimiter);
bool parse_redir(t_redir *redir,t_token **tokens);
t_tree *cmdnode();
t_tree *pipenode(t_tree *left, t_tree *right);
void add_back_redir(t_redir **lst,t_redir *new);
t_redir *ft_lastlst_redir(t_redir *node);
#endif