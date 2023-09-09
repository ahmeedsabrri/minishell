/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:31:47 by asabri            #+#    #+#             */
/*   Updated: 2023/09/09 14:50:31 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
int space_found(char *str)
{
	int i;

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
void lexer3(t_init *in,char *line,t_env *env)
{
	t_token *ptr;
	char **token;
	int i;

	i = -1;
	token = NULL;
	if (!in->space)
	{
		token = get_word(line,&in->i,env,in->h);
		if (!token || !token[0])
			add_back(&in->token,newtoken(WORD,NOT_QOUTE,NULL,in->h));
		else 
			while (token[++i])
				add_back(&in->token,newtoken(WORD,NOT_QOUTE,token[i],in->h));
		in->space = 1;
		in->h = 0;
	}
	else
	{
	   	ptr = in->token;
		while (ptr->next)
			ptr = ptr->next;
		token = get_word(line,&in->i,env,ptr->herdoc);
		ptr->value = ft_strjoin(ptr->value,token[0]);
		while (token[++i])
			add_back(&in->token,newtoken(WORD,NOT_QOUTE,token[i],in->h));
	}
}

void lexer2(t_init *in,char *line,t_env *env)
{
	t_token *ptr;
	char **token;
	
	if (!in->space)
	{
		token = get_q(line,line[in->i - 1],&in->i,(in->dq == 1),in->h,env);
		add_back(&in->token,newtoken(WORD,QOUTE,token[0],in->h));
		in->space = 1;
		in->h = 0;
	}
	else
	{
		ptr = in->token;
		while (ptr->next)
			ptr = ptr->next;
		if (ptr->is_qoute == NOT_QOUTE)
			ptr->is_qoute = QOUTE;
		token = get_q(line,line[in->i - 1],&in->i,(in->dq == 1),ptr->herdoc,env);
		ptr->value = ft_strjoin(ptr->value,token[0]);
	}
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
			add_back(&in->token,newtoken(which_flag(line[in->i],1),NOT_QOUTE,NULL,0));
			in->i++;
			if (which_flag(line[in->i], 1) == HEREDOC)
				in->h = 1;
		}
		else 
			add_back(&in->token,newtoken(which_flag(line[in->i],0),NOT_QOUTE,NULL,0));
	}
	else if (line[in->i] == '|')
	{   
		add_back(&in->token,newtoken(which_flag(line[in->i],0),NOT_QOUTE,ft_strdup("|"),0));
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
	in->h = 0;
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
				add_back(&in.token, newtoken(WORD,QOUTE, "", 0));
				in.space = 1;
			}
			else
			{
				ptr = in.token;
				while (ptr->next)
				ptr = ptr->next;
				if (ptr->is_qoute == NOT_QOUTE)
					ptr->is_qoute = QOUTE;
	   			ptr->value = ft_strjoin(ptr->value,"");
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
	add_back(&in.token, newtoken(END,END, "newline",0));
	if (in.dq || in.sq)
		return(fd_printf(2, "Syntax: Error Unclosed quote\n"),NULL);
	return (in.token);
}
