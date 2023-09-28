/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 04:39:49 by asabri            #+#    #+#             */
/*   Updated: 2023/09/28 01:49:58 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexer4(t_init *in)
{
	t_token	*ptr;

	if (!in->space) 
	{
		add_back(&in->token, newtoken(WORD, QOUTE, "", 0));
		in->space = 1;
	}
	else
	{
		ptr = in->token;
		while (ptr->next)
			ptr = ptr->next;
		if (ptr->is_qoute == NOT_QOUTE)
			ptr->is_qoute = QOUTE;
		ptr->value = ft_strjoin(ptr->value, "");
	}
	in->i++;
}

void	ft_intia(t_init *in, t_env *env)
{
	in->token = NULL;
	in->i = -1;
	in->dq = 0;
	in->sq = 0;
	in->space = 0;
	in->h = 0;
	in->env = env;
}

int	space_found(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] == ' ')
			return (1);
	}
	return (0);
}

t_token_type	which_flag(char c, bool bol)
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
