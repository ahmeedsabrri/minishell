/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:46:16 by yamajid           #+#    #+#             */
/*   Updated: 2023/09/28 12:06:32 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_need(char c)
{
	if (c == '-') 
		return (0);
	return (1);
}

int	cd_cases(t_env **env, char **argv)
{
	if (access(argv[1], F_OK))
	{
		ft_putstr_fd("minishell cd: ", STDOUT_FILENO);
		ft_putstr_fd(ft_strdup_env(argv[1]), STDOUT_FILENO);
		ft_putstr_fd(" : no such file or directory: \n", STDOUT_FILENO);
		return (0);
	}
	else if ((access(argv[1], X_OK) == 0 
			|| access(argv[1], W_OK) == 0 || access(argv[1], R_OK) == 0))
	{
		if (chdir(argv[1]) == 0)
		{
			update_pwd(env, argv);
			return (1);
		}
	}
	else if (access(argv[1], X_OK) != 0
		|| access(argv[1], W_OK) != 0 || access(argv[1], R_OK) != 0)
	{
		ft_putstr_fd("minishell: cd:", STDOUT_FILENO);
		ft_putstr_fd(argv[1], STDOUT_FILENO);
		ft_putstr_fd(" : Permission denied \n", STDOUT_FILENO);
		return (0);
	}
	return (1);
}

int	cd_home(t_env **env, char **argv)
{
	char	*str;

	str = get_home_path(env);
	if (!str)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDOUT_FILENO);
		return (0);
	}
	if (!chdir(str))
	{
		update_pwd(env, argv);
		return (1);
	}
	else
	{
		printf("minishell: can't change to home directory\n");
		return (0); 
	}
	return (1);
}

void	cd_command(char **argv, t_env **env)
{
	if (argv[1] == NULL || ft_strcmp(argv[1], "~") == 0)
	{
		if (cd_home(env, argv) == 0)
		{
			cd_home(env, argv);
			_status(1);
			return ;
		}
	}
	else if (argv[1] != NULL)
	{
		if (argv[0] && argv[1])
		{
			if (cd_cases(env, argv) == 0)
			{
				_status(1);
				return ;
			}
		}
	}
	return ;
}
