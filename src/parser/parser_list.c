/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:45:18 by asabri            #+#    #+#             */
/*   Updated: 2023/09/01 01:05:50 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

t_redir *ft_lastlst_redir(t_redir *node)
{
	if (!node)
		return (NULL);
	while (node->next)
	{
        if (node->next == NULL)
			return (node);
		node = node->next;
	}
	return (node);
}
void add_back_redir(t_redir **lst,t_redir *new)
{
    t_redir *ptr;

    ptr = (*lst);
    if (*lst == NULL)
    {
        *lst = new;
        return;
    }
    ptr = ft_lastlst_redir(*(lst));
    ptr->next = new;
}
