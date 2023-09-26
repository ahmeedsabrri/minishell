/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 02:40:01 by asabri            #+#    #+#             */
/*   Updated: 2023/09/24 09:42:37 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree	*parse_cmd(t_token **tokens, t_env *env)
{
	t_tree	*tree;

	if (!((*tokens)->type == WORD || check_redir((*tokens)->type)))
		return (NULL);
	tree = cmdnode();
	while (((*tokens)->type == WORD || check_redir((*tokens)->type)))
	{
		if ((*tokens)->type == WORD)
			add_back(&((t_simplecmd *)tree)->simplecmd, 
				newtoken(WORD, (*tokens)->is_qoute, (*tokens)->value, 0));
		else if (!parse_redir(&((t_simplecmd *)tree)->redir_list, tokens, env))
			return (NULL);
		(*tokens) = (*tokens)->next;
	}
	return (tree);
}

t_tree	*parse_pipe(t_token **tokens, t_env *env)
{
	t_tree	*tree;

	tree = parse_cmd(tokens, env);
	if (!tree)
		return (NULL);
	while ((*tokens)->type == PIPE)
	{
		*tokens = (*tokens)->next;
		tree = pipenode(tree, parse_cmd(tokens, env));
		if (!tree->right)
			return (NULL);
	}
	return (tree);
}

t_tree	*parser(t_token *tokens, t_env *env)
{
	t_tree	*tree;

	if (!tokens)
		return (NULL);
	if (tokens->type == END)
		return (NULL);
	tree = parse_pipe(&tokens, env);
	if ((!tree || tokens->type != END) && tokens->type != SIGNAL)
	{
		_status(258);
		return (fd_printf(2, "synatx: Error near unexpected token `%s'\n"
				, tokens->value), NULL);
	}
	return (tree);
}
