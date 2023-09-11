/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 05:44:08 by asabri            #+#    #+#             */
/*   Updated: 2023/09/11 18:09:49 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

bool check_redir(t_token_type flage)
{
    if (flage == RIN || flage == ROUT || flage == APPEND || flage == HEREDOC)
        return (true);
    return (false);
}

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
