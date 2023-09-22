/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:16:08 by asabri            #+#    #+#             */
/*   Updated: 2023/09/22 00:41:05 by asabri           ###   ########.fr       */
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
    if (!env[0])
    {
        str = malloc(sizeof(char *) * 3);
        str[0] = ft_strdup_env("PATH");
        str[1] = ft_strdup_env(PATH);
        str[2] = NULL;
        add_var_back(&myenv,newvar(str));
        return (free(str),printf("❌olny path in the environment❌\n"),myenv);
    }
    while(env[++i])
    {
        str = takevar(env[i]);
        add_var_back(&myenv, newvar(str));
        free(str);
    }
    return(myenv);                                                                     
}