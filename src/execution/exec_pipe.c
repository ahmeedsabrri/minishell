/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:17:39 by asabri            #+#    #+#             */
/*   Updated: 2023/09/20 02:10:06 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void close_p(int fd[2])
{
    close(fd[0]);
    close(fd[1]);
}
int piping_pross(t_tree *tree,t_env *env,int fd[2],int std,char **_env)
{
    pid_t pid;
    
    pid = fork();
    if (pid == -1)
        return (perror("Fork Error"),0);
    if (pid == 0)
    {
        if (dup2(fd[std],std) == -1)
            return (perror("Dup2 Error"),exit(1),0);
        close_p(fd);
        execution(tree,&env,_env);
        _status(g_global_exit);
        exit(g_global_exit);
    } 
    return (pid); 
}
void exec_pipe(t_tree *tree,t_env *env,char **_env)
{
    int fd[2];
    int pid[2];
    int status;
    
    pipe(fd);
    pid[0] = piping_pross(((t_pipeline *)tree)->left,env,fd,1,_env);
    if (!pid[0])
        return ;
    pid[1] = piping_pross(((t_pipeline *)tree)->right,env,fd,0,_env);
    if (!pid[1])
        return ;
    close_p(fd);
    waitpid(pid[1],&status,0);
    _status(status);
    while (wait(NULL) != -1);
}