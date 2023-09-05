/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:04:19 by asabri            #+#    #+#             */
/*   Updated: 2023/09/05 11:43:47 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft-42/libft.h"
# include "ft_malloc.h"
# include "lexer.h"
# include "parser.h"
# include "exec.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
#include <errno.h>

int g_global_exit;

typedef struct s_env
{
    char *var;
    char *val;
    struct s_env *next;
    char *prev;
    int exit_status;
    int print_err;
    int chdir_result;
}t_env;


t_env *dup_env(char **env);
t_env *newvar(char **variable);
char **takevar(char *str);
void	add_var_back(t_env **lst, t_env *new);
t_env	*ft_lstlast(t_env *node);

t_token	*ft_lexer(char *line,t_env *env);
t_token *ft_lastlst(t_token *node);
void add_back(t_token **lst,t_token *new);
t_token *newtoken(t_token_type flag,char *token,int _herdoc);
char *get_word(char *str, int *index,t_env *env,int herdoc);
char *get_q(char *str,char c,int *index,bool expnd,int herdoc,t_env *env);
char *ft_expand(char *str,t_env *env);
t_token_type which_flag(char c, bool bol);
void _status(int s);
void    sig_handler(int signum);

void execution(t_tree *tree,t_env **env,char **_env);
// ------------------------------builtins------------------------------
void pwd();
void cd(int args_count, char **args, t_env **env);
void	echo(int argc, char **argv);
void env_var(char **argv, t_env *env);
int unset(char *variable, t_env **env_list);
int export(char *variable, t_env **env);
void _env(t_env *env);
void exit_built(int args_count, char **input);
t_env *find_env(t_env *env, char *name);
t_env *dup_env(char **env);
int check_identifier(char *identifier);
void export_alone(t_env *env);
int	built_ins(char **argv,t_env *env,int argc);
////////////////////////////////parser
t_tree *parser(t_token *tokens,t_env *env);
t_tree *parse_pipe(t_token **tokens,t_env *env);
t_tree *parse_cmd(t_token **tokens,t_env *env);
int ft_herdoc(char *delimiter,t_env *env, int mode);
bool parse_redir(t_redir **redir,t_token **tokens,t_env *env);
t_tree *cmdnode();
t_tree *pipenode(t_tree *left, t_tree *right);
void add_back_redir(t_redir **lst,t_redir *new);
t_redir *ft_lastlst_redir(t_redir *node);
bool check_redir(t_token_type flage);
#endif