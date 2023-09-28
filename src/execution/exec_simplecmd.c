/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simplecmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 08:46:16 by asabri            #+#    #+#             */
/*   Updated: 2023/09/28 08:58:56 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	run_cmd_sc(t_tree *tree, t_env **env, char **arg)
{
	while (((t_simplecmd *)tree)->redir_list && 
		check_redir(((t_simplecmd *)tree)->redir_list->type) && 
		redir_creation(((t_simplecmd *)tree)->redir_list, *env))
		((t_simplecmd *)tree)->redir_list = 
			((t_simplecmd *)tree)->redir_list->next;
	if (arg[0])
		exec_cmd(tree, *env, arg);
	exit(0);
	return (0);
}

void	exec_redir_sc(t_tree *tree, t_env **env)
{
	pid_t	pid;
	int		status;
	char	**arg;
	char	**args;
	int		list_len;

	arg = list_to_array_env(((t_simplecmd *)tree)->simplecmd, &list_len);
	if (is_bulting(arg[0]))
	{
		redir_creation(((t_simplecmd *)tree)->redir_list, *env);
		if (built_ins(arg, env, list_len) || !arg[0])
			return ;
	}
	args = list_to_array(((t_simplecmd *)tree)->simplecmd, &list_len);
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		return ;
	}
	if (!pid)
		run_cmd_sc(tree, env, args);
	waitpid(pid, &status, 0);
	exit_status(status);
}
