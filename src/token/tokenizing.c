/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:31:47 by asabri            #+#    #+#             */
/*   Updated: 2023/07/02 02:13:21 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



// utils 
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

t_token *newtoken(char *tok,int hdoc,int expnd)
{
    t_token *node;

    node = malloc(sizeof(t_token));
    node->token = tok;
    node->next = NULL;
    node->bottom = NULL;
    node->hd = false;
    node->expand = false;
    if (hdoc)
        node->hd = true;
    if (expnd)
        node->expand = true;
    return (node);
}
char *get_word(char *str, int index ,char c)
{
    int j;

    j = index;
    while (str[j] && !ft_strchr("\"\'<>()\t", str[j]))
        j++;
    return (ft_substr(str,index,j - 1));
}


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
int onlyspace(int i, char *str)
{
    while(str[i] && str[i] == ' ')
        i++;
    if (str[i])
        return (0);
    else 
        return (1);
}
//-----------------------functions that give meanig to the line---------------------------

void lexer_2(t_init *t, char *str)
{
    if(str[t->i] == '\'')
        t->singl_quote = !t->singl_quote;
    else if(str[t->i] == '\"')
        t->double_quote = !t->double_quote;
    else if(ft_strchr("<>",str[t->i]) && str[t->i] == str[t->i + 1])
        t->unkown = 1;
    else if (str[t->i] != '\"' || str[t->i] != '\'')
        t->space = true;
    else if (str[t->i] == '(')
        t->op += 1;
    else if (str[t->i] == ')')
        t->cp += 1;
    if (!onlyspace(t->i,str) && str[t->i] != '\'' && str[t->i] != '\"' 
        && str[t->i] != ' ' && str[t->i] != '\t')
        add_token_back(&t->token,newtoken())
}

void lexer_1(t_init *in, char *tok)
{
    if (in->space)
    {   
        add_token_back(newtoken(),)
        in->space = false;
    }
    else if(!in->space)
    {
        
    }
}


// main function that use everthing 
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
            lexer_2(&init,line);
        else if (!ft_strchr("\"\'<>() \t", line[init->i]) && (!init->double_quote|| !init->singl_quote))
            
    }
    
    return (NULL);
}