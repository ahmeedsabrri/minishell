/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 09:39:06 by asabri            #+#    #+#             */
/*   Updated: 2023/09/25 23:52:00 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_lstsize_env(t_env *list)
{
	int	i;

	i = 0;
	if (!list)
		return (0);
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

char	**env_to_arr(t_env *env)
{
	int		len;
	char	**arr;
	int		i;
	t_env	*ptr;

	ptr = env;
	len = ft_lstsize_env(ptr);
	arr = ft_malloc(sizeof(char *) * (len + 1), 1);
	i = 0;
	while (ptr)
	{
		arr[i] = ft_strjoin(ft_strdup(ptr->var), "=");
		arr[i] = ft_strjoin(arr[i], ft_strdup(ptr->val));
		i++;
		ptr = ptr->next;
	}
	arr[i] = 0;
	return (arr);
}
