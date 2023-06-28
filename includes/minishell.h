/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:04:19 by asabri            #+#    #+#             */
/*   Updated: 2023/06/14 02:58:35 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft-42/libft.h"
# include "./ft_malloc.h"
# include "./token.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
    char *var;
    char *val;
    struct s_env *next;
}t_env;

typedef struct  s_tree
{
    int type;
}        t_tree;

typedef struct s_pipeline
{
    int type;
    t_tree *left;
    t_tree *right;

    
}t_pipeline;

typedef struct s_cmdline
{
    int type;
    t_token *cmd;
    t_token *redir;
}t_cmdline;

t_env *dup_env(char **env);
t_env *newvar(char **variable);
char **takevar(char *str);
void	add_var_back(t_env **lst, t_env *new);
t_env	*ft_lstlast(t_env *node);

t_token *strtoken(char *str);
t_token *newtoken(char *variable);
void	add_token_back(t_token **lst, t_token *new);
t_token	*ft_lstlst(t_token *node);
#endif