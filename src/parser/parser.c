/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 02:40:01 by asabri            #+#    #+#             */
/*   Updated: 2023/08/31 06:08:32 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"


t_tree *parse_cmd(t_token **tokens)
{
    t_token *cmd;
    t_token *redir;
    t_tree *tree;
    
    while((*tokens)->type == WORD || check_redir((*tokens)->type))
    {
        tree = cmdnode();
        cmd = ((t_simplecmd *)tree)->simplecmd;
        redir = ((t_simplecmd *)tree)->redir_list;
        if((*tokens)->type == WORD)
            add_back(&cmd, newtoken(WORD, (*tokens)->value));
        else
            
        
    }
}

t_tree *parse_pipe(t_token **tokens)
{
    t_tree *tree;
    
    tree = parse_cmd(tokens);
    if(!tree)
        return(NULL);
}

t_tree *parser(t_token *tokens)
{
    t_tree *tree;

    tree = parse_pipe(&tokens);
}