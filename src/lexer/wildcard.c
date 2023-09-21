/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:22:58 by asabri            #+#    #+#             */
/*   Updated: 2023/09/20 00:19:46 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
int start_with(char *str)
{
       if (str[0] == '.')
              return 1;
       return 0;
}
void ft_wildcard(t_init *in,char *patarn,int *index)
{
    int i;
    int count;
    char *p;
    DIR *dir;
    if (!*index)
        i = *index + 1;
    else
        i = 0;
    count = 0;
    if (patarn[i] && patarn[i] != ' ')
    {
        while (patarn[i] && patarn[i] != ' ')
        {
            if (patarn[i]!= '*')
                count++;
            i++;
        }
        i = *index + 1;
        int j;
        j = 0;
        p = ft_malloc(sizeof(char) * count + 1, 1);
        while (patarn[i] && patarn[i] != ' ')
        {
            if (patarn[i]!= '*')
            {
                p[j] = patarn[i];  
                j++;
            }
            i++;
        }
        *index +=count;
    }
    else
    {
        while (patarn[i] && patarn[i] == '*')
            i++;
        char *current;
        
        current = getcwd(NULL, 0);
        dir = opendir(current);
        struct dirent *entity;
        entity = readdir(dir);
        if (!entity){
            *index += 1;
            return ;
        }
        while (entity)
        {
            if (!start_with(entity->d_name) && entity)
                add_back(&in->token,newtoken(WORD,NOT_QOUTE,entity->d_name,0));
            entity = readdir(dir);
        }
        *index += i;
        closedir(dir);
    }
        
}