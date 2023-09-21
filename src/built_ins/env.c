/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:33:11 by yelwadou          #+#    #+#             */
/*   Updated: 2023/09/21 02:54:14 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void my_env(t_env **env)
{
    t_env *ptr;

    ptr = *env;
    if(!ptr)
        return ;
    while (ptr)
    {
        if ((ptr)->val)
            printf("%s=%s\n", (ptr)->var, (ptr)->val);
        ptr = (ptr)->next;
    }
    _status(0);
}
