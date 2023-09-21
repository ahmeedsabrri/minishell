/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:18:31 by asabri            #+#    #+#             */
/*   Updated: 2023/09/21 05:14:59 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

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
        return (fd_printf(2,"Minishell: %s: No such file or directory\n",arg),exit(127),NULL);
    }
    cmd = ft_strjoin("/",arg);
    while (env)
    {
        if (ft_strcmp(env->var,"PATH") == 0)
            whole_path = ft_strdup(env->val);
        env = env->next;
    }
    if (!whole_path)
        return (fd_printf(2,"Minishell: %s: No such file or directory\n",arg),exit(127),NULL);
    path = ft_split(whole_path,':');
    if (!path)
        return (NULL);
    while (path[++i])
    {
        vpath = ft_strjoin(path[i],cmd);
        if (!access(vpath,X_OK))
            return (vpath);
    }
    return (NULL);
}
void exec_cmd(t_tree *tree,t_env *env,char **_env,char **arg)
{
    (void)tree;
    char *vpath;
   
    vpath = validpath(arg[0],env);
    signal(SIGQUIT,SIG_DFL);
    if (!vpath && ft_strchr(arg[0],'/'))
        exit(127);
    execve(vpath,arg,_env);
    fd_printf(2,"Minishell %s: command not found:\n",arg[0]);
    exit(127);
}
