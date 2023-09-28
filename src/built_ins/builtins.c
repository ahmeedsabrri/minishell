/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 03:39:16 by asabri            #+#    #+#             */
/*   Updated: 2023/09/28 11:47:07 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	built_ins(char **argv, t_env **env, int argc)
{
	if (ft_strcmp(argv[0], "env") == 0)
		return (my_env(env), 1);
	else if (ft_strcmp(argv[0], "pwd") == 0)
	{
		return (pwd(env), 1);
		return (1);
	}
	else if (ft_strcmp(argv[0], "exit") == 0)
		exit_built(argc, argv);
	else if (ft_strcmp(argv[0], "echo") == 0)
		return (echo(argc, argv), 1);
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (unset(env, argv, argc), 1);
	else if (ft_strcmp(argv[0], "export") == 0)
	{
		if (argc == 1)
			return (export_alone(*env), 1);
		else
			return (export(argv, env, argc), 1);
	}
	else if (ft_strcmp(argv[0], "cd") == 0)
		return (cd_command (argv, env), 1);
	return (0);
}
