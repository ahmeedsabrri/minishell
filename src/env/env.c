/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:16:08 by asabri            #+#    #+#             */
/*   Updated: 2023/09/27 00:46:55 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*dup_env(char **env)
{
	t_env	*myenv;
	char	**str;
	int		i;

	i = -1;
	str = NULL;
	myenv = NULL;
	if (!env[0])
	{
		str = ft_malloc(sizeof(char *) * 3, 2);
		str[0] = ft_strdup_env("PATH");
		str[1] = ft_strdup_env(PATH);
		str[2] = NULL;
		add_var_back(&myenv, newvar(str));
		return (printf("❌olny path in the environment❌\n"), myenv);
	}
	while (env[++i])
	{
		str = takevar(env[i]);
		add_var_back(&myenv, newvar(str));
		free(str);
	}
	return (myenv);
}
