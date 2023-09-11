/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:12:45 by asabri            #+#    #+#             */
/*   Updated: 2023/09/11 14:13:11 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void vsSEE(t_tree *tree)
{
    if(!tree)
        return ;
    if(tree->type == PIPE)
    {
        t_pipeline *pipe = (t_pipeline *)tree;
        vsSEE(pipe->left);
        // printf("l_%d\n",pipe->left->type);
        printf("|");
        vsSEE(pipe->right);
        
    }
    else if (tree->type == REDIRECTION)
    {
         while (((t_redircmd *)tree)->redir_list)
        {
            printf("%s\n", ((t_redircmd *)tree)->redir_list->open_file);
            ((t_redircmd *)tree)->redir_list = ((t_redircmd *)tree)->redir_list->next;
        }
    }
    else if (tree->type == WORD)
    {
        
        while (((t_simplecmd *)tree)->simplecmd && tree->type != PIPE)
        {
            printf("%s\n", ((t_simplecmd *)tree)->simplecmd->value);
            ((t_simplecmd *)tree)->simplecmd = ((t_simplecmd *)tree)->simplecmd->next;
        } 
    }
    
}

int main(int ac, char **av, char **env)
{
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
        // vsSEE(tree);
        if(*line)
            add_history(line);
    }
    return 0;
}
