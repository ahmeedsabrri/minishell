/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:32:41 by yelwadou          #+#    #+#             */
/*   Updated: 2023/09/21 03:01:07 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void echo(int argc, char **argv)
{
    bool n_option;
    int i;
    
    i = 1;
    n_option = false;
      
    if (argc > 1 && argv[1] && strcmp(argv[1], "-n") == 0)
    {
        n_option = true;
        i++;
    }
    while (i < argc)
    {
      if (i < argc - 1) {
        printf("%s ", argv[i]);
      }
      else {
        printf("%s", argv[i]);
      }
      i++;
    }
    if (!n_option) {
      printf("\n");
    }
}