/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 04:21:58 by asabri            #+#    #+#             */
/*   Updated: 2023/09/21 10:06:09 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void execution(t_tree *tree,t_env **env)
{
    if (tree->type == PIPE)
        exec_pipe(tree,*env);
    else if (tree->type == WORD)
        exec_redir(tree, env);
    return ;
}