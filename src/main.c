/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:12:45 by asabri            #+#    #+#             */
/*   Updated: 2023/09/09 14:31:50 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// bool signalset = false;
// void   (*SIGINT_handler)(int);
// void ignore_signal_for_shell()
// {
// 	signalset = true;
	
// 	// ignore "Ctrl-C"
    
//     SIGINT_handler = signal(SIGINT, SIG_IGN);
// 	// ignore "Ctrl-Z"
//     signal(SIGTSTP, SIG_IGN);
// 	// ignore "Ctrl-\"
//     signal(SIGQUIT, SIG_IGN);
// }
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
void _status(int s)
{
    g_global_exit = s;
}

void    sig_handler(int signum)
{
    (void)signum;
    if (waitpid(-1, NULL, WNOHANG) == 0)
        return ;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();

}


int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    char *line;
    t_env *envrm;
    t_token *token;
    t_tree *tree;
    
    signal(SIGQUIT, SIG_IGN);
    rl_catch_signals = 0;
    envrm = dup_env(env);
    token = NULL;
    tree = NULL;
    while(1)
    {
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
