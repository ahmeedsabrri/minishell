/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 02:40:01 by asabri            #+#    #+#             */
/*   Updated: 2023/09/11 14:29:03 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"
void sig_herdoc(int fd[2])
{
    int ttfd;
    
    ttfd = open(ttyname(STDERR_FILENO), O_RDONLY);
    if (ttfd == -1)
        return (close(fd[1]),close(fd[0]),fd_printf(2,"sig_error"));
    close(fd[1]);
    close(fd[0]);
}
void herdoc_handler_(int param)
{
    (void)param;
    close(STDIN_FILENO);
}
int ft_herdoc(char *delimiter,t_env *env,t_token_type is_qoute)
{
    int fd[2];
    char *line;
    char **token;

    token = malloc(sizeof(char *) * 2);
    if (pipe(fd) == -1)
        return(fd_printf(2,"error"),0);
    signal(SIGINT,herdoc_handler_);
    while (isatty(STDIN_FILENO))
    {
        line = readline(">");
        if (!line || !ft_strcmp(line,delimiter))
        {
            free(line);
            break;
        }
        if (is_qoute == NOT_QOUTE && ft_strchr(line,'$'))
        {
            token = ft_expand(line,env,0);
            line = token[0];
            token[1] = NULL;
        }
        fd_printf(fd[1],"%s\n",line);
        free(line);
    }
    signal(SIGINT,sig_handler);
    if (!isatty(STDIN_FILENO))
        return (sig_herdoc(fd),_status(1),0);
    return (close(fd[1]),fd[0]);
}

bool parse_redir(t_redir **redir,t_token **tokens,t_env *env)
{
    t_redir *node;
    node = malloc(sizeof(t_redir));
    if (!node)
        return (false);
    node->type = (*tokens)->type;
    (*tokens) = (*tokens)->next;
    if((*tokens)->type != WORD)
        return (false);
    node->open_file = (*tokens)->value;
    node->file_flages = O_RDONLY;
    if (node->type == ROUT || node->type == APPEND)
        node->file_flages |= O_CREAT | O_WRONLY | ((node->type == ROUT) * O_TRUNC + !(node->type == ROUT) * O_APPEND);
    else if (node->type == HEREDOC)
        node->in_fd = ft_herdoc((*tokens)->value,env, (*tokens)->is_qoute);
    if (node->type == HEREDOC && !node->in_fd)
        return ((*tokens)->type = SIGNAL,false);
    node->next = NULL;
    add_back_redir(redir,node);
    return (true);
}

bool check_redir(t_token_type flage)
{
    if (flage == RIN || flage == ROUT || flage == APPEND || flage == HEREDOC)
        return (true);
    return (false);
}

t_tree *parse_cmd(t_token **tokens,t_env *env)
{
    t_tree *tree;
    if(!((*tokens)->type == WORD || check_redir((*tokens)->type)))
        return(NULL);
    tree = cmdnode();
    while(((*tokens)->type == WORD || check_redir((*tokens)->type)))
    {
        if((*tokens)->type == WORD)
            add_back(&((t_simplecmd *)tree)->simplecmd, newtoken(WORD,(*tokens)->is_qoute, (*tokens)->value, 0));
        else if(!parse_redir(&((t_simplecmd *)tree)->redir_list,tokens,env))
            return (NULL);
        (*tokens) = (*tokens)->next;
    }
    return (tree);
}

t_tree *parse_pipe(t_token **tokens,t_env *env)
{
    t_tree *tree;
    
    tree = parse_cmd(tokens,env);
    if(!tree)
        return(NULL);
    while((*tokens)->type == PIPE)
    {
        *tokens = (*tokens)->next;
        tree = pipenode(tree, parse_cmd(tokens,env));
        if (!((t_pipeline *)tree)->right)
            return (NULL);
    }
    return(tree);
}

t_tree *parser(t_token *tokens,t_env *env)
{
    t_tree *tree;
    if(!tokens)
        return(NULL);
    if (tokens->type == END)
        return (NULL);
    tree = parse_pipe(&tokens,env);
    if((!tree || tokens->type != END) && tokens->type != SIGNAL)
        return(fd_printf(2,"synatx: Error near unexpected token `%s'\n", tokens->value),NULL);
    return (tree);
}