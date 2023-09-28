/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:17:39 by asabri            #+#    #+#             */
/*   Updated: 2023/09/28 08:18:37 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_p(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

int	piping_pross(t_tree *tree, t_env *env, int fd[2], int std)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("Fork Error"), 0);
	if (pid == 0)
	{
		if (dup2(fd[std], std) == -1)
			return (perror("Dup2 Error"), exit(1), 0);
		close_p(fd);
		execution(tree, &env);
		_status(g_global_exit);
		exit(g_global_exit);
	}
	return (pid); 
}

void	exec_pipe(t_tree *tree, t_env *env)
{
	int	fd[2];
	int	pid[2];
	int	status;

	pipe(fd);
	pid[0] = piping_pross(tree->left, env, fd, 1);
	if (!pid[0])
		return ;
	pid[1] = piping_pross(tree->right, env, fd, 0);
	if (!pid[1])
		return ;
	close_p(fd);
	waitpid(pid[1], &status, 0);
	exit_status(status);
	while (wait(NULL) != -1)
		;
}
