/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:45:34 by yamajid           #+#    #+#             */
/*   Updated: 2023/09/21 00:40:56 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"



void pwd(t_env **env)
{
    char *pwd;
    (void)env;
    // pwd = get_env_var(env, "PWD");
    pwd = getcwd(NULL, 0);
    if (pwd)
    {
        ft_putstr_fd(pwd, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
    }
}
