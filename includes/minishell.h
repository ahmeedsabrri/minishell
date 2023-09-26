/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:04:19 by asabri            #+#    #+#             */
/*   Updated: 2023/09/26 00:17:29 by asabri           ###   ########.fr       */
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
# include <errno.h>
# include <sys/types.h>
# include <dirent.h>
# define PATH "/Users/asabri/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Library/Frameworks/Mono.framework/Versions/Current/Commands:/Users/asabri/.brew/bin"

int g_global_exit;

typedef struct s_env
{
	char *var;
	char *val;
	struct s_env *next;
}t_env;
typedef struct s_norm
{
	t_token *token;
	t_env   *env;
	t_tree *tree;
	int in;
	int out;
}t_norm;

// ------------------------------env------------------------------
t_env	*dup_env(char **env);
t_env	*newvar(char **variable);
char	**takevar(char *str);
void	add_var_back(t_env **lst, t_env *new);
t_env	*ft_lstlast(t_env *node);
char	**env_to_arr(t_env *env);
// ------------------------------lexer------------------------------
t_token	*ft_lexer(char *line, t_env *env);
t_token	*ft_lastlst(t_token *node);
void	add_back(t_token **lst, t_token *new);
t_token			*newtoken(t_token_type flag, t_token_type _qoute, 
					char *token, int _herdoc);
char			**get_word(char *str, int *index, t_env *env, int herdoc);
char	**get_q(char *str,char c,int *index,bool expnd,int herdoc,t_env *env);
char			**ft_expand(char *str,t_env *env,int mode);
void			lexer4(t_init *in);
t_token_type	which_flag(char c, bool bol);
int		space_found(char *str);
void	ft_intia(t_init *in);
void _status(int s);
void    sig_handler(int signum);
void exit_status(int status);
// ------------------------------exectution------------------------------
void execution(t_tree *tree,t_env **env);
void exec_pipe(t_tree *tree,t_env *env);
int piping_pross(t_tree *tree,t_env *env,int fd[2],int std);
void close_p(int fd[2]);
void exec_redir(t_tree *tree,t_env **env);
int redir_creation(t_redir *redir,t_env *env);
int is_bulting(char *cmd);
void exec_cmd(t_tree *tree,t_env *env,char **arg);
char *validpath(char *arg,t_env *env);
int	ft_lstsize(t_token *list);
char **list_to_array(t_token *simplecmd,int *len);
// ------------------------------builtins------------------------------
int	built_ins(char **argv,t_env **env,int argc);
char *get_env_var(t_env **env, char *key);
void set_env_var(t_env **env, char *key, char *value);
void ft_add_to_val(t_env **env, char *key);
void update_pwd(t_env **env, char **argv);
void cd_command(char **argv, t_env **env);
void echo(int argc, char **argv);
void my_env(t_env **env);
void exit_built(int args_count, char **input);
int export(char **argv, t_env **env, int argc);
void pwd(t_env **env);
void unset(t_env **env, char **argv, int argc);
void export_alone(t_env *env);
// ------------------------------parsing------------------------------e
t_tree *parser(t_token *tokens,t_env *env);
t_tree *parse_pipe(t_token **tokens,t_env *env);
t_tree *parse_cmd(t_token **tokens,t_env *env);
int ft_herdoc(char *delimiter,t_env *env,t_token_type is_qoute);
bool parse_redir(t_redir **redir,t_token **tokens,t_env *env);
t_tree *cmdnode();
t_tree *redirnode();
t_tree *pipenode(t_tree *left, t_tree *right);
void add_back_redir(t_redir **lst,t_redir *new);
t_redir *ft_lastlst_redir(t_redir *node);
bool check_redir(t_token_type flage);

#endif