/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:33:11 by yelwadou          #+#    #+#             */
/*   Updated: 2023/09/05 03:45:05 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void _env(t_env *env)
{
    if(!env)
        return ;
    while (env)
    {
        printf("%s=%s\n", env->var, env->val);
        env = env->next;
    }
    _status(0);
    //open("ldbjf", O_APPEND)
}
//  TODO:need to make sure if it should be printed in stdout_fileno