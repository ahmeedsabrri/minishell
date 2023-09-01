/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:04:19 by asabri            #+#    #+#             */
/*   Updated: 2023/08/31 20:59:10 by asabri           ###   ########.fr       */
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
# include <fcntl.h>

typedef struct s_env
{
    char *var;
    char *val;
    struct s_env *next;
}t_env;


t_env *dup_env(char **env);
t_env *newvar(char **variable);
char **takevar(char *str);
void	add_var_back(t_env **lst, t_env *new);
t_env	*ft_lstlast(t_env *node);

t_token	*ft_lexer(char *line,t_env *env);
t_token *ft_lastlst(t_token *node);
void add_back(t_token **lst,t_token *new);
t_token *newtoken(t_token_type flag,char *token);
char *get_word(char *str, int *index,t_env *env);
char *get_q(char *str,char c,int *index,bool expnd,int herdoc,t_env *env);
char *ft_expand(char *str,t_env *env);
t_token_type which_flag(char c, bool bol);
#endif