/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:31:47 by asabri            #+#    #+#             */
/*   Updated: 2023/08/31 05:51:04 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void lexer3(t_init *in,char *line,t_env *env)
{
	t_token *ptr;
	
	if (!in->space)
	{
		add_back(&in->token,newtoken(WORD,get_word(line,&in->i,env)));
		in->space = 1;
	}
	else
	{
	   ptr = in->token;
		while (ptr->next)
			ptr = ptr->next;
	   ptr->value = ft_strjoin(ptr->value,get_word(line,&in->i,env));
	}
}

void lexer2(t_init *in,char *line,t_env *env)
{
	t_token *ptr;
	
	if (!in->space)
	{
		add_back(&in->token,newtoken(WORD,get_q(line,line[in->i - 1],&in->i,(in->dq == 1),in->h,env)));
		in->space = 1;
	}
	else
	{
		ptr = in->token;
		while (ptr->next)
			ptr = ptr->next;
		ptr->value = ft_strjoin(ptr->value,get_q(line,line[in->i - 1],&in->i,(in->dq == 1),in->h,env));
	}
	in->h = 0;
}
void lexer1(t_init *in,char *line)
{
	(line[in->i] == '\"')&& (in->dq = !in->dq);
	(line[in->i] == '\'') && (in->sq = !in->sq);
	if (line[in->i] == '<' || line[in->i] == '>')
	{
		in->h = 0;
		if(line[in->i] == line[in->i + 1])
		{
			add_back(&in->token,newtoken(which_flag(line[in->i],1),NULL));
			in->i++;
			if (which_flag(line[in->i], 1) == HEREDOC)
				in->h = 1;
		}
		else 
			add_back(&in->token,newtoken(which_flag(line[in->i],0),NULL));
	}
	else if (line[in->i] == '|')
	{   
		add_back(&in->token,newtoken(which_flag(line[in->i],0),NULL));
		in->h = 0;
	}
	(line[in->i] != '\"' && line[in->i] != '\'') && (in->space = 0);
}

void ft_intia(t_init *in)
{
	in->token = NULL;
	in->i = -1;
	in->dq = 0;
	in->sq = 0;
	in->space = 0;
}

t_token	*ft_lexer(char *line,t_env *env)
{
	int i;
	t_init in;
	t_token *ptr;

	i = -1;
	ft_intia(&in);
	while(line[++in.i])
	{
		if((line[in.i] == '\"' && line[in.i] == line[in.i + 1]) || (line[in.i] == '\'' && line[in.i] == line[in.i + 1]))
		{   
			if(!in.space) 
			{
				add_back(&in.token, newtoken(WORD, NULL));
				in.space = 1;
			}
			else
			{
				ptr = in.token;
				while (ptr->next)
				ptr = ptr->next;
	   			ptr->value = ft_strjoin(ptr->value,NULL);
			}	
			in.i++;
		}
		else if(((in.dq && line[in.i] != '\"') || (in.sq && line[in.i] != '\'')))
			lexer2(&in,line,env);
		else if (ft_strchr("<>\'\"| \t",line[in.i]))
			lexer1(&in,line);
		else if (!ft_strchr("<>\'\"| \t",line[in.i]))
			lexer3(&in,line,env);
	}
	add_back(&in.token, newtoken(END, "newline"));
	if (in.dq || in.sq)
		return(fd_printf(2, "Syntax Error: Unclosed quote\n"),NULL);
	return (in.token);
}
