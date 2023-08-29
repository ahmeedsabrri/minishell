/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 08:38:29 by asabri            #+#    #+#             */
/*   Updated: 2023/08/29 11:39:56 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
char *get_word(char *str, int *index)
{
    int i;
    int j;

    i = *index;
    j = i;
    while (str[i] && !ft_strchr("\"\'|<>() \t", str[i]))
		i++;
    *index = i - 1;
    return (ft_substr(str, j, i - j));
}
char *get_q(char *str,char c,int *index)
{
    int i;
    int j;

    i = *index;
    j = i;
    while (str[i] && str[i] != c)
		i++;
    *index = i - 1;
    return (ft_substr(str, j, i - j));
}
t_token *ft_lastlst(t_token *node)
{
	if (!node)
		return (NULL);
	while (node->next)
	{
		node = node->next;
	}
	return (node);
}
void add_back(t_token **lst,t_token *new)
{
    t_token *ptr;

    ptr = *lst;
    if (*lst == NULL)
    {
        *lst = new;
        return;
    }
    ptr = ft_lastlst(*(lst));
    ptr->next = new;
}
t_token *newtoken(char *token)
{
    t_token *lst;
    
    lst = ft_malloc(sizeof(t_token),1);
    lst->value = token;
    lst->next = NULL;
    return (lst);
}