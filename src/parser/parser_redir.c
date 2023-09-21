/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:08:45 by asabri            #+#    #+#             */
/*   Updated: 2023/09/21 03:56:58 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

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

    if (pipe(fd) == -1)
        return(fd_printf(2,"error"),0);
    signal(SIGINT,herdoc_handler_);
    while (isatty(STDIN_FILENO))
    {
        line = readline("> ");
        if (!line || !ft_strcmp(line,delimiter))
        {
            free(line);
            break;
        }
        if (is_qoute == NOT_QOUTE && ft_strchr(line,'$'))
        {
            token = ft_expand(line,env,0);
            fd_printf(fd[1],"%s\n",token[0]);
        }
        else
        {
            fd_printf(fd[1],"%s\n",line);
            free(line);  //mybe leak here
        }
    }
    if (!isatty(STDIN_FILENO))
        return (close(fd[1]),close(fd[0]),_status(1),0);
    return (close(fd[1]),fd[0]);
}

bool parse_redir(t_redir **redir,t_token **tokens,t_env *env)
{
    t_redir *node;
    node = ft_malloc(sizeof(t_redir), 1);
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