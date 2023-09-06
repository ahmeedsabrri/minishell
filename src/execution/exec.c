/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 04:21:58 by asabri            #+#    #+#             */
/*   Updated: 2023/09/06 10:53:07 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"
void execution(t_tree *tree,t_env **env,char **_env);
/////////////////////////////////////////////////////REDIR
int redir_creation(t_redir *redir,t_env *env)
{
    (void)env;
    int fd;
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
        dup2(redir->in_fd,STDIN_FILENO);   
        return (close(redir->in_fd),exit(1),1);
    }
    return(0);
}

void exec_redir(t_tree *tree,t_env *env,char **_env)
{
    (void)_env;
    while(((t_simplecmd *)tree)->redir_list && check_redir(((t_simplecmd *)tree)->redir_list->type) && 
        redir_creation(((t_simplecmd *)tree)->redir_list,env))
        ((t_simplecmd *)tree)->redir_list = ((t_simplecmd *)tree)->redir_list->next;
}
/////////////////////////////////////////////////////CMD
int	ft_lstsize(t_token *list)
{
	int	i;

	i = 0;
	if (!list)
		return (0);
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

char *validpath(char *arg,t_env *env)
{
    char *cmd;
    int i;
    char **path;
    char *vpath;
    char *whole_path;

    i = -1;
    if(ft_strchr(arg, '/'))
    {
        if (!access(arg,X_OK))
            return(arg);
        return (fd_printf(2,"Minishell: %s: No such file or directory\n",arg),NULL);
    }
    cmd = ft_strjoin("/",arg);
    while (env)
    {
        if (!ft_strcmp(env->var,"PATH"))
            whole_path = ft_strdup(env->val);
        env = env->next;
    }
    path = ft_split(whole_path,':');
    
    while (path[++i])
    {
        vpath = ft_strjoin(path[i],cmd);
        if (!access(vpath,X_OK))
            return (vpath);
    }
    return (NULL);
}
void exec_cmd(t_tree *tree,t_env *env,char **_env)
{
    char **arg;
    int i;
    char *vpath;
    int status;
    int list_len;
    pid_t pid;

    i = 0;
    list_len = ft_lstsize(((t_simplecmd *)tree)->simplecmd) ;
    arg = malloc(sizeof(char *) * (list_len + 1));
    while(((t_simplecmd *)tree)->simplecmd)
    {
        arg[i++] = ft_strdup(((t_simplecmd *)tree)->simplecmd->value);
        ((t_simplecmd *)tree)->simplecmd = ((t_simplecmd *)tree)->simplecmd->next;
    }
    arg[i] = NULL;
    i = -1;
    vpath = validpath(arg[0],env);
    pid = fork();
    if (!pid)
    {
        signal(SIGQUIT,SIG_DFL);
        exec_redir(tree,env,_env);
        if (built_ins(arg,env,list_len) || !arg[0])
            exit(0);
        if (!vpath && ft_strchr(arg[0],'/'))
            exit(127);
        execve(vpath,arg,_env);
        fd_printf(2,"Minishell %s: command not found:\n",arg[0]);
        exit(127);
    }
    waitpid(pid,&status,0);
    if (WIFEXITED(status))
        _status(WEXITSTATUS(status));
    else if (WIFSIGNALED(status) )
    {
      _status( 128 + WTERMSIG(status));
      if (WTERMSIG(status) == SIGQUIT)
        fd_printf(2, "Quit: %d\n", SIGQUIT);
    }
}
/////////////////////////////////////////////////////PIPE
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

void execution(t_tree *tree,t_env **env,char **_env)
{
    
    if (tree->type == PIPE)
        exec_pipe(tree,*env,_env);
    else if (tree->type == WORD)
        exec_cmd(tree,*env,_env);
}