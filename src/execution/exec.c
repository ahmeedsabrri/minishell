/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 04:21:58 by asabri            #+#    #+#             */
/*   Updated: 2023/09/28 08:41:23 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**list_to_array(t_token *simplecmd, int *len)
{
	int		i;
	char	**arg;

	i = 0;
	*len = ft_lstsize(simplecmd);
	arg = ft_malloc(sizeof(char *) * (*len + 1), 1);
	while (simplecmd)
	{
		arg[i++] = ft_strdup(simplecmd->value);
		simplecmd = simplecmd->next;
	}
	arg[i] = NULL;
	return (arg);
}

char	**list_to_array_env(t_token *simplecmd, int *len)
{
	int		i;
	char	**arg;

	i = 0;
	*len = ft_lstsize(simplecmd);
	arg = ft_malloc(sizeof(char *) * (*len + 1), 2);
	while (simplecmd)
	{
		arg[i++] = ft_strdup(simplecmd->value);
		simplecmd = simplecmd->next;
	}
	arg[i] = NULL;
	return (arg);
}

int	is_bulting(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else
		return (0);
}

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

void	execution(t_tree *tree, t_env **env)
{
	if (!tree)
		return ;
	else if (tree->type == PIPE)
		exec_pipe(tree, *env);
	else if (tree->type == WORD)
		exec_redir(tree, env);
	return ;
}
