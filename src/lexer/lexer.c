/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:31:47 by asabri            #+#    #+#             */
/*   Updated: 2023/08/28 14:51:24 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
void ft_intia(t_init *in)
{
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
    t_token *token;
    t_init in;

    i = -1;
    ft_intia(&in);
    while(line[++i])
    {
        if(in.dq && line[i] == '\"' || in.sq && line[i] == '\'')
    }
}
