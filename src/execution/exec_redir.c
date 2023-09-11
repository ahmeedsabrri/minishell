/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:19:32 by asabri            #+#    #+#             */
/*   Updated: 2023/09/11 15:04:14 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"


int is_bulting(char *cmd)
{
    if (!ft_strcmp(cmd,"cd"))
        return (1);
    else if (!ft_strcmp(cmd,"echo"))
        return (1);
    else if (!ft_strcmp(cmd,"export"))
        return (1);
    else if (!ft_strcmp(cmd,"unset"))
        return (1);
    else if (!ft_strcmp(cmd,"pwd"))
        return (1);
    else if (!ft_strcmp(cmd,"env"))
        return (1);
    else if (!ft_strcmp(cmd,"exit"))
        return (1);
    else
        return (0);
}
int redir_creation(t_redir *redir,t_env *env)
{
    (void)env;
    int fd;
    if(!redir)
        return (0);
    if (redir->type != HEREDOC)
    {
        fd = open(redir->open_file,redir->file_flages, 0664);
        if (fd == -1)
            return (perror("fd error"),0);
        if(redir->type == ROUT || redir->type == APPEND)
            dup2(fd,STDOUT_FILENO);
        else
            dup2(fd,STDIN_FILENO);
        return (close(fd),1);
    }
    else
    {
        if (dup2(redir->in_fd,STDIN_FILENO) == -1)
            return (perror(" dup2 Error"),exit(1),0);
    }
    return(0);
}
char **list_to_array(t_token *simplecmd,int *len)
{

    int i;
    char **arg;

    i = 0;
    *len = ft_lstsize(simplecmd);
    arg = malloc(sizeof(char *) * (*len + 1));
    while(simplecmd)
    {
        arg[i++] = ft_strdup(simplecmd->value);
        simplecmd = simplecmd->next;
    }
    arg[i] = NULL;
    return (arg);
}

void exec_redir(t_tree *tree,t_env *env,char **_env)
{
    pid_t pid;
    int status;
    int list_len;
    char **arg;

    arg = list_to_array(((t_simplecmd *)tree)->simplecmd,&list_len);
    if (is_bulting(arg[0]))
    {
        redir_creation(((t_simplecmd *)tree)->redir_list,env);
        if (built_ins(arg,env,list_len) || !arg[0])
            return ;
    }
    pid = fork();
    if (!pid)
    {
        while(((t_simplecmd *)tree)->redir_list && check_redir(((t_simplecmd *)tree)->redir_list->type) && 
                redir_creation(((t_simplecmd *)tree)->redir_list,env))
            ((t_simplecmd *)tree)->redir_list = ((t_simplecmd *)tree)->redir_list->next;
        exec_cmd(tree,env,_env,arg);
        exit(0);
    }
    waitpid(pid,&status,0);
    exit_status(status);
}
