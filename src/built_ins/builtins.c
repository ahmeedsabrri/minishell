/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 03:39:16 by asabri            #+#    #+#             */
/*   Updated: 2023/09/22 01:53:50 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	built_ins(char **argv,t_env **env,int argc)
{
	if (ft_strcmp(argv[0], "env") == 0)
		return (my_env(env),1);
	else if (ft_strcmp(argv[0], "pwd") == 0)
	{
		return (pwd(env),1);
		return (1);
	}
	else if (ft_strcmp(argv[0], "exit") == 0)
		exit_built(argc, argv);
	else if (ft_strcmp(argv[0], "echo") == 0)
		return (echo(argc, argv),1);
	else if (ft_strcmp(argv[0], "unset") == 0)
	{
		unset(env , argv, argc);
		return (1);
	}
	else if (ft_strcmp(argv[0], "export") == 0)
	{
		if (argc == 1)
		{
			export_alone(*env);
			return (1);
		}
		else
		{
			export(argv, env, argc);
			return (1);
		}
	}
	else if (ft_strcmp(argv[0], "cd") == 0)
	{
		cd_command (argv, env);
		return (1);
	}
return (0);
}
