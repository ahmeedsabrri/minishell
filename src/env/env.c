/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:16:08 by asabri            #+#    #+#             */
/*   Updated: 2023/09/12 03:18:07 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env *dup_env(char **env)
{
    t_env *myenv;
    char **str;
    int i;
    
    i = -1;
    str = NULL;
    myenv = NULL;
    while(env[++i])
    {
        str = takevar(env[i]);
        add_var_back(&myenv, newvar(str));
        free(str);
    }
    return(myenv);                                                                     
}