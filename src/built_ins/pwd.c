/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:45:34 by yamajid           #+#    #+#             */
/*   Updated: 2023/09/22 02:41:47 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"



void pwd(t_env **env)
{
    char *pwd;
    pwd = get_env_var(env, "PWD");
    if (pwd)
    {
        // ft_putstr_fd(pwd, STDOUT_FILENO);
        // ft_putstr_fd("\n", STDOUT_FILENO);
        fd_printf(1,"%s\n",pwd);
    }
}
