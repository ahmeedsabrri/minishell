/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 08:38:29 by asabri            #+#    #+#             */
/*   Updated: 2023/09/28 05:48:58 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_word(char *str, int *index, t_env *env, int herdoc)
{
	int		i;
	int		j;
	char	**s;

	s = ft_malloc(sizeof(char *) * 2, 1);
	i = *index;
	j = i;
	while (str[i] && !ft_strchr("\"\'|<> \t", str[i]))
		i++;
	*index = i - 1;
	if (herdoc)
		return (s[0] = ft_substr(str, j, i - j), s[1] = NULL, s);
	return (ft_expand(ft_substr(str, j, i - j), env, 1));
}

char	**get_q(char *str, t_init *in, int *index, int herdoc)
{
	int		i;
	int		j;
	char	**s;

	s = ft_malloc(sizeof(char *) * 2, 1);
	i = *index;
	j = i;
	while (str[i] && str[i] != str[*index - 1])
		i++;
	*index = i - 1;
	if (in->dq && !herdoc)
		return (ft_expand(ft_substr(str, j, i - j), in->env, 0));
	return (s[0] = ft_substr(str, j, i - j), s[1] = NULL, s);
}

t_token	*ft_lastlst(t_token *node)
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

void	add_back(t_token **lst, t_token *new)
{
	t_token	*ptr;

	ptr = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ptr = ft_lastlst(*(lst));
	ptr->next = new;
}

t_token	*newtoken(t_token_type flag, t_token_type _qoute, 
			char *token, int _herdoc)
{
	t_token	*lst;

	lst = ft_malloc(sizeof(t_token), 1);
	lst->value = token;
	lst->type = flag;
	lst->herdoc = _herdoc;
	lst->is_qoute = _qoute;
	lst->next = NULL;
	return (lst);
}
