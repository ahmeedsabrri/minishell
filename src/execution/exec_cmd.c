/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:18:31 by asabri            #+#    #+#             */
/*   Updated: 2023/09/28 06:05:44 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_executable(char *arg)
{
	if (!access(arg, X_OK))
		return (arg);
	return (fd_printf(2, "Minishell: %s: No such file or directory\n", arg), 
		exit(127), NULL);
}

char	*get_path(t_env *env)
{
	char	*path;

	path = NULL;
	while (env)
	{
		if (ft_strcmp(env->var, "PATH") == 0)
			path = ft_strdup(env->val);
		env = env->next;
	}
	return (path);
}

char	*search_in_path(char *arg, t_env *env)
{
	char	*cmd;
	int		i;
	char	**path;
	char	*vpath;
	char	*whole_path;

	i = -1;
	cmd = ft_strjoin("/", arg);
	whole_path = get_path(env);
	if (!whole_path)
		return (fd_printf(2, "Minishell: %s: No such file or directory\n", arg), 
			exit(127), NULL);
	path = ft_split(whole_path, ':');
	if (!path)
		return (NULL);
	while (path[++i])
	{
		vpath = ft_strjoin(path[i], cmd);
		if (!access(vpath, X_OK))
			return (vpath);
	}
	return (NULL);
}

char	*validpath(char *arg, t_env *env)
{
	if (ft_strchr(arg, '/'))
		return (check_executable(arg));
	else
		return (search_in_path(arg, env));
	return (NULL);
}

void	exec_cmd(t_tree *tree, t_env *env, char **arg)
{
	char	*vpath;
	char	**_env;

	(void)tree;
	vpath = validpath(arg[0], env);
	_env = NULL;
	_env = env_to_arr(env);
	signal(SIGQUIT, SIG_DFL);
	if (!vpath && ft_strchr(arg[0], '/'))
		exit(127);
	execve(vpath, arg, _env);
	fd_printf(2, "Minishell %s: command not found:\n", arg[0]);
	exit(127);
}
