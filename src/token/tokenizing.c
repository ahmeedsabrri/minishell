/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:31:47 by asabri            #+#    #+#             */
/*   Updated: 2023/06/23 05:30:44 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_lstlst(t_token *node)
{
	if (!node)
		return (NULL);
	while (node)
	{
		if (node->next == NULL)
			return (node);
		node = node ->next;
	}
	return (node);
}

void	add_token_back(t_token **lst, t_token *new)
{
	t_token	*ptr;

	ptr = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		ptr = ft_lstlst(*(lst));
		ptr->next = new;
	}
}

t_token *newtoken(char *tok)
{
    t_token *node;
    int i;

    i = -1;
    node = malloc(sizeof(t_token));
    node->token = tok;
    node->next = NULL;
    return (node);
}
// char *get_word(char *str, int index ,char c)
// {
//     int j;

//     j = index;
//     while (str[j] && str[j] != c)
//         j++;
//     return (ft_substr(str,index,j - 1));
// }
void ft_initialize(t_init *init)
{
    init->i = -1;
    init->bottom = 0;
    init->token = 0;
    init->unkown = 0;
    init->cp = 0;
    init->op = 0;
    init->double_quote = false;
    init->singl_quote = false;
    init->space = false;
}


void lexer_2()
{
    
}
void lexer_1(t_init *in, char *tok)
{
    if (in->space)
    {
        
        in->space = false;
    }
    else if(!in->space)
    {
        
    }
}
t_token *strtoken(char *line)
{
    t_token *token;
    t_init *init;

    tf_initialize(&init);
    while (line[++(init->i)])
    {
        if ((init->double_quote && line[init->i] =='\"') || (init->singl_quote && line[init->i] == '\''))
            lexer_1(&init,line);
        else if (ft_strchr("\"\'<>()\t", line[init->i]))
        
        else if (!ft_strchr("\"\'<>() \t", line[init->i]) && (!init->double_quote|| !init->singl_quote))
    }
    return (NULL);
}