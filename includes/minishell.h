/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:04:19 by asabri            #+#    #+#             */
/*   Updated: 2023/07/09 22:41:53 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft-42/libft.h"
# include "ft_malloc.h"
# include "lexer.h"
# include "parser.h"
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



t_cmd *token(char *line);
t_env *dup_env(char **env);
t_env *newvar(char **variable);
char **takevar(char *str);
void	add_var_back(t_env **lst, t_env *new);
t_env	*ft_lstlast(t_env *node);

// t_token *strtoken(char *str);
// t_token *newtoken(t_flgs type,char *tok,int hdoc,int expnd);
t_cmd *newtoken(char *cmd);
void add_token_back(t_cmd **lst, t_cmd *new);
t_cmd	*ft_lstlst(t_cmd *lst);
#endif