/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:12:45 by asabri            #+#    #+#             */
/*   Updated: 2023/08/29 11:27:46 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **env)
{
    char *line;
    (void)ac;
    (void)av;
    (void)env;
    // t_env *envrm;
    // envrm = dup_env(env);
    t_token *token;
    token = NULL;
    while(1)
    {
        
        line = readline("minishell-$ ");
        if (line == NULL)
            break;
        token = ft_lexer(line);
        while(token)
        {
            printf("%s\n",token->value);
            token = token->next;
        }
        if(*line)
            add_history(line);
    }
    return 0;
}
