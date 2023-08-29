/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:31:47 by asabri            #+#    #+#             */
/*   Updated: 2023/08/29 13:12:48 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
void lexer3(t_init *in,char *line)
{
    if (!in->space)
    {
        add_back(&in->token,newtoken(get_word(line,&in->i)));
        in->space = 1;
        // printf("%s",in->token->value);
        // exit(0);
    }
    else
    {
        while (in->token->next)
            in->token = in->token->next;
       in->token->value = ft_strjoin(in->token->value,get_word(line,&in->i));
    }
}
void lexer2(t_init *in,char *line)
{
    if (!in->space)
    {
        add_back(&in->token,newtoken(get_q(line,line[in->i - 1],&in->i)));
        in->space = 1;
    }
    else
    {
    
        while (in->token->next)
            in->token = in->token->next;
        in->token->value = ft_strjoin(in->token->value,get_q(line,line[in->i - 1],&in->i));
    }
}
void lexer1(t_init *in,char *line)
{
    if (line[in->i] == '\"')
        in->dq = !in->dq;
    else if (line[in->i] == '\'')
        in->sq = !in->sq;
    else if (line[in->i] == '<' && line[in->i + 1])
        in->h +=1;
    else if (line[in->i] == '|' && (!in->dq || !in->sq))
    {
        add_back(&in->token,newtoken("|"));
        in->space = !in->space;
    }
    (line[in->i] != '\"') && (in->space = 0);
}

void ft_intia(t_init *in)
{
    in->token = NULL;
    in->i = -1;
    in->dq = 0;
    in->sq = 0;
    in->space = 0;
    in->cp = 0;
    in->op = 0;
    in->h = 0;
}

t_token	*ft_lexer(char *line)
{
    int i;
    t_init in;

    i = -1;
    ft_intia(&in);
    while(line[++in.i])
    {
        if((in.dq && line[in.i] != '\"') || (in.sq && line[in.i] != '\''))
            lexer2(&in,line);
        else if (strchr("<>\'\"| \t",line[in.i]))
            lexer1(&in,line);
        else if (!strchr("<>\'\"| \t",line[in.i]))
            lexer3(&in,line);
    }
    if (in.dq || in.sq)
    {
        printf("error");
        exit(1);
    }
    return (in.token);
}
