/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 02:40:01 by asabri            #+#    #+#             */
/*   Updated: 2023/07/12 08:10:27 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

t_tree *parser(t_token **cmd)
{
    t_tree	*tree;

	if (!*cmd || (*cmd)->type == END)
		return (NULL);
	tree = parse_oper(cmd);
	if ((!tree || (*cmd)->type != END) && (*cmd)->type != SIGHER)
	{
		set_statu(258);
		fd_printf(2, "Syntax : Error unexpected token `%s'\n", (*cmd)->token);
		return (NULL);
	}
	return (tree);
}
