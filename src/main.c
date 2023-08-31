/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:12:45 by asabri            #+#    #+#             */
/*   Updated: 2023/08/31 02:35:31 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    char *line;
    t_env *envrm;
    t_token *token;
    
    envrm = dup_env(env);
    token = NULL;
    while(1)
    {
        
        line = readline("minishell-$ ");
        if (line == NULL)
            break;
        token = ft_lexer(line,envrm);
        while(token)
        {
            printf("%s\t",token->value);
            if (token->type == WORD)
                printf("WORD");
            if (token->type == PIPE)
                printf("PIPE");
            if (token->type == RIN)
                printf("RIN");
            if (token->type == ROUT)
                printf("ROUT");
            if (token->type == APPEND)
                printf("APPEND");
            if (token->type == HEREDOC)
                printf("HEREDOC");
            token = token->next;
            printf("\n");
        }
        if(*line)
            add_history(line);
    }
    return 0;
}
