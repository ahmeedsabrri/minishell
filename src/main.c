/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:12:45 by asabri            #+#    #+#             */
/*   Updated: 2023/09/12 03:51:56 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void vsSEE(t_tree *tree)
// {
//     if(!tree)
//         return ;
//     if(tree->type == PIPE)
//     {
//         t_pipeline *pipe = (t_pipeline *)tree;
//         vsSEE(pipe->left);
//         // printf("l_%d\n",pipe->left->type);
//         printf("|");
//         vsSEE(pipe->right);
        
//     }
//     else
//     {
//         while (((t_simplecmd *)tree)->redir_list)
//         {
//             printf("%s\n", ((t_simplecmd *)tree)->redir_list->open_file);
//             ((t_simplecmd *)tree)->redir_list = ((t_simplecmd *)tree)->redir_list->next;
//         }
//         // while (((t_simplecmd *)tree)->simplecmd && tree->type != PIPE)
//         // {
//         //     printf("%s\n", ((t_simplecmd *)tree)->simplecmd->value);
//         //     ((t_simplecmd *)tree)->simplecmd = ((t_simplecmd *)tree)->simplecmd->next;
//         // } 
//     }
// }
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
		free(ptr->prev);
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
    atexit(ff);
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
    // ft_malloc(0,1);
    while(1)
    {
        // ft_malloc(0,0);
        ft_malloc(0,1);
        dup2(in,STDIN_FILENO);
        dup2(out,STDOUT_FILENO);
        signal(SIGINT,sig_handler);
        line = readline("minishell-$ ");
        if (!line)
            break;
        token = ft_lexer(line,envrm);
        tree = parser(token,envrm);
        if (tree)
            execution(tree,&envrm,env);
        if(*line)
            add_history(line);
        free (line);
        ft_malloc(0,0);
    }
    listclear_env(&envrm);
    ft_malloc(0,0);
    return 0;
}
