/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:12:45 by asabri            #+#    #+#             */
/*   Updated: 2023/08/25 17:47:57 by asabri           ###   ########.fr       */
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
    while(1)
    {
        
        line = readline("minishell-$ ");
        if (line == NULL)
            break;
        token = strtoken(line);
        // if (strcmp(token->token,"env") == 0)
        // {
        //     while(envrm)
        //     {
        //         printf("%s",envrm->var);
        //         printf("=");
        //         printf("%s\n",envrm->val);
        //         envrm = envrm->next;
        //     }
        // }
        while(token)
        {
            printf("%s ",token->token);
            token = token->next;
        }
        if(*line)
            add_history(line);
    }
    return 0;
}
