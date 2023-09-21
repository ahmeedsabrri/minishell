/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:33:24 by yelwadou          #+#    #+#             */
/*   Updated: 2023/09/21 08:29:02 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void unset(t_env **env, char **argv, int argc)
{
    int i;
    t_env *ptr;
    t_env *prev;

    i = 1;
    
    while (i < argc)
    {
        prev = NULL;
        ptr = *env;
        while (ptr)
        {
            if (ft_strcmp(argv[i], ptr->var) == 0)
            {
                if (prev == NULL) // the head of the list is being deleted
                    *env = ptr->next;
                else
                    prev->next = ptr->next;
                free(ptr->var);
                free(ptr);
                break; // node deleted, exit the while loop
            }
            prev = ptr;
            ptr = ptr->next;
        }
        i++;
    }

    // ptr = *env;
    //       while (ptr)
    //     {
    //         printf("*%s*\n", ptr->var);
    //         ptr = ptr->next;
    //     }
}


