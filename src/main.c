/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:12:45 by asabri            #+#    #+#             */
/*   Updated: 2023/07/14 08:35:54 by asabri           ###   ########.fr       */
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
    t_cmd *cmd;
    while(1)
    {
        
        line = readline("minishell-$ ");
        if (line == NULL)
            break;
        cmd = token(line);
        while (cmd)
        {
            printf("%s",cmd->cmd);
            cmd = cmd->next;
        }
        if(*line)
            add_history(line);
    }
    return 0;
}
