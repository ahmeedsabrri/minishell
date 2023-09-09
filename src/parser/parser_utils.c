/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 05:44:08 by asabri            #+#    #+#             */
/*   Updated: 2023/09/08 09:20:18 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

t_tree *pipenode(t_tree *left, t_tree *right)
{
    t_pipeline *n;

    n = malloc(sizeof(t_pipeline));
    return(n->left = left, n->right = right, n->type = PIPE, (t_tree *)n);
}
t_tree *cmdnode()
{
    t_simplecmd *n;
    n = malloc(sizeof(t_simplecmd));
    return(n->redir_list = NULL,n->simplecmd = NULL, n->type = WORD, (t_tree *)n);
}

// t_tree *redirnode()
// {
//     t_redircmd *n;
//     n = malloc(sizeof(t_redircmd));
//     return(n->redir_list = NULL, n->type = REDIRECTION, (t_tree *)n);
// }