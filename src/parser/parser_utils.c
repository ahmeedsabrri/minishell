/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 05:44:08 by asabri            #+#    #+#             */
/*   Updated: 2023/09/25 22:12:04 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_redir(t_token_type flage)
{
	if (flage == RIN || flage == ROUT || flage == APPEND || flage == HEREDOC)
		return (true);
	return (false);
}

t_tree	*pipenode(t_tree *left, t_tree *right)
{
	t_tree	*n;

	n = ft_malloc(sizeof(t_tree), 1);
	return (n->left = left, n->right = right, n->type = PIPE, n);
}

t_tree	*cmdnode(void)
{
	t_simplecmd	*n;

	n = ft_malloc(sizeof(t_simplecmd), 1);
	return (n->redir_list = NULL, 
		n->simplecmd = NULL, n->type = WORD, (t_tree *)n);
}
