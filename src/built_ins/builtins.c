/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 03:39:16 by asabri            #+#    #+#             */
/*   Updated: 2023/09/05 05:27:26 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
int	built_ins(char **argv,t_env *env,int argc)
{
    
	if (ft_strcmp(argv[0], "env") == 0)
		return (_env(env),1);
	// if (ft_strcmp(argv[0], "unset") == 0 && argc > 1)
	// 	unset(argv[1], &env);
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (pwd(),1);
	if (ft_strcmp(argv[0], "exit") == 0)
		exit_built(argc, argv);
	if (ft_strcmp(argv[0], "echo") == 0)
		return (echo(argc, argv),1);
	// if (ft_strcmp(argv[0], "export") == 0)
	// {
	// 	if (argc == 1)
	// 		export_alone(env);
	// 	else
	// 		export(argv[1], &env);
	// }
	// if (ft_strcmp(argv[0], "cd") == 0)
	// 	cd(argc, argv, &env);
return (0);
}