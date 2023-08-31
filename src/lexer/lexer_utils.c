/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 04:39:49 by asabri            #+#    #+#             */
/*   Updated: 2023/08/31 04:40:20 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_type which_flag(char c, bool bol)
{
    if (c == '|')
        return (PIPE);
    else if (bol && c == '>')
        return (APPEND);
    else if (bol && c == '<')
        return (HEREDOC);
    else if (c == '>')
        return (ROUT);
    else if (c == '<')
        return (RIN);
    else
        return (WORD);
}