/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:12:45 by asabri            #+#    #+#             */
/*   Updated: 2023/09/21 04:07:53 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	listclear_env(t_env **head)
{
	t_env	*tmp;
	t_env	*ptr;

	if (!head)
		return ;
	tmp = *head;
	while (tmp)
	{
		ptr = tmp;
		tmp = tmp->next;
		free(ptr->var);
		free(ptr->val);
		free(ptr);
	}
	*head = NULL;
}
void ff()
{
    system("leaks minishell");
}
int main(int ac, char **av, char **env)
{
    // atexit(ff);
    (void)ac;
    (void)av;
    char *line;
    t_env *envrm;
    t_token *token;
    t_tree *tree;
    int in;
    int out;
    
    in = dup(0);
    out = dup(1);
    signal(SIGQUIT, SIG_IGN);
    rl_catch_signals = 0;
    envrm = dup_env(env);
    token = NULL;
    tree = NULL;

    while(1)
    {
        dup2(in,STDIN_FILENO);
        dup2(out,STDOUT_FILENO);
        signal(SIGINT,sig_handler);
        line = readline("minishell-$ ");
        if (!line)
            break;
        token = ft_lexer(line,envrm);

        // while (token)
        // {
        //     printf("%s\n",token->value);
        //     token = token->next;
        // }
        tree = parser(token,envrm);
        if (tree)
            execution(tree,&envrm,env);
        if(*line)
            add_history(line);
        free (line);
    }
    listclear_env(&envrm);
    return 0;
}
