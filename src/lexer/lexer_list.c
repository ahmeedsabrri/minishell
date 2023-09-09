/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 08:38:29 by asabri            #+#    #+#             */
/*   Updated: 2023/09/09 14:30:35 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
char **get_word(char *str, int *index,t_env *env,int herdoc)
{
    int i;
    int j;
    char **s;

    s = malloc(sizeof(char *) * 2);
    i = *index;
    j = i;
    while (str[i] && !ft_strchr("\"\'|<> \t", str[i]))
		i++;
    *index = i - 1;
    if (herdoc)
        return (s[0] = ft_substr(str, j, i - j),s[1] = NULL,s);
    return (ft_expand(ft_substr(str, j, i - j),env,1));
}
char **get_q(char *str,char c,int *index,bool expnd,int herdoc,t_env *env)// bool expand // (dq == true) ila kan bool expand == 1 ghatexpandi ila kan 0 rak nta f single quote
{
    int i;
    int j;
    char **s;

    s = malloc(sizeof(char *) * 2);
    i = *index;
    j = i;
    while (str[i] && str[i] != c)
		i++;
    *index = i - 1;
    if (expnd && !herdoc)
        return (ft_expand(ft_substr(str, j, i - j),env,0));
    return (s[0] = ft_substr(str, j, i - j),s[1] = NULL,s);  //return (expand(ft_substr(str, j, i - j))); ila kan false atreturni  return (ft_substr(str, j, i - j));
}
t_token *ft_lastlst(t_token *node)
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
t_token *newtoken(t_token_type flag,t_token_type _qoute,char *token,int _herdoc)
{
    t_token *lst;
    
    lst = malloc(sizeof(t_token));
    lst->value = token;
    lst->type = flag;
    lst->herdoc = _herdoc;
    lst->is_qoute = _qoute;
    lst->next = NULL;
    return (lst);
}