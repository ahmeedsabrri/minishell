/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 02:40:01 by asabri            #+#    #+#             */
/*   Updated: 2023/09/01 01:46:04 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"
int ft_herdoc(char *delimiter)
{
    int fd[2];
    char *line;
    if (pipe(fd) == -1)
        return(fd_printf(2,"error"),0);
    while (1)
    {
        line = readline(">");
        if (!line || !ft_strcmp(line,delimiter))
            break;
        fd_printf(fd[1],"%s\n",line);
        free(line);
    }
    return (close(fd[1]),fd[0]);
}

bool parse_redir(t_redir *redir,t_token **tokens)
{
    t_redir *node;
    node = malloc(sizeof(t_redir));
    node->type = (*tokens)->type;
    (*tokens) = (*tokens)->next;
    if((*tokens)->type != WORD)
        return (puts("here"), false);
    node->open_file = (*tokens)->value;
    node->file_flages = O_RDONLY;
    if (node->type == ROUT || node->type == APPEND)
        node->file_flages = O_CREAT | O_WRONLY | ((node->type == ROUT) * O_TRUNC + !(node->type == ROUT) * O_APPEND);
    else if (node->type == HEREDOC)
        node->in_fd = ft_herdoc((*tokens)->value);
    node->next = NULL;
    add_back_redir(&redir,node);
    return (true);
}

bool check_redir(t_token_type flage)
{
    if (flage == RIN || flage == ROUT || flage == APPEND || flage == HEREDOC)
        return (true);
    return (false);
}

t_tree *parse_cmd(t_token **tokens)
{
    t_token *cmd;
    t_redir *redir;
    t_tree *tree;
    
    tree = NULL;
    while((*tokens) && ((*tokens)->type == WORD || check_redir((*tokens)->type)))
    {
        tree = cmdnode();
        cmd = ((t_simplecmd *)tree)->simplecmd;
        redir = ((t_simplecmd *)tree)->redir_list;
        if((*tokens)->type == WORD)
            add_back(&cmd, newtoken(WORD, (*tokens)->value));
        else if(!parse_redir(redir,tokens))
            return (NULL);
        (*tokens) = (*tokens)->next;
    }
    return (tree);
}

t_tree *parse_pipe(t_token **tokens)
{
    t_tree *tree;
    
    tree = parse_cmd(tokens);
    if(!tree)
        return(NULL);
    while((*tokens)->type == PIPE)
    {
        *tokens = (*tokens)->next;
        tree = pipenode(tree, parse_cmd(tokens));
        if(!((t_pipeline *)tree)->right)
            return (NULL);
    }
    return(tree);
}

t_tree *parser(t_token *tokens)
{
    t_tree *tree;

    tree = parse_pipe(&tokens);
    if(!tree ||  tokens->type != END)
        return(fd_printf(2,"synatx error\n"),NULL);
    return (tree);
}