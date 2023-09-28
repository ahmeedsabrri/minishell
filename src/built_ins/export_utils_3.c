/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:51:55 by yamajid           #+#    #+#             */
/*   Updated: 2023/09/28 12:09:58 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_cut(char *str, char c)
{
	int		i;
	char	*ptr;

	ptr = NULL;
	i = search_lenght(str, c);
	ptr = ft_strndup(str, i);
	return (ptr);
}

void	change_value_if_not(t_env **env, char *str)
{
	t_env	*ptr;

	ptr = *env;
	while (ptr)
	{
		if (strcmp(ptr->var, ft_cut(str, '=')) == 0)
		{
			if (ptr->val != NULL)
				ptr->val = "\0";
			else if (ptr->val == NULL)
				ptr->val = "\0";
			else if (ptr->val[0] == '\0')
				ptr->val = ft_substr_env(str, search_lenght(str, '=') + 1, 
						ft_strlen(str) - search_lenght(str, '='));
		}
		ptr = ptr->next;
	}
}

void	change_value_if_exist(t_env **env, char *str)
{
	t_env	*ptr;

	ptr = *env;
	while (ptr)
	{
		if (ft_strcmp(ptr->var, ft_cut(str, '=')) == 0)
		{
			if (ptr->val == NULL || !ptr->val[0] || ptr->val[0])
				ptr->val = ft_substr_env(str, search_lenght(str, '=') + 1,
						ft_strlen(str) - search_lenght(str, '='));
			return ;
		}
		ptr = ptr->next;
	}
}

int	ft_search_for_plus(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i++]) 
		if (str[i] == c && str[i + 1] == '=')
			return (1);
	return (0);
}

int	for_plus(t_env **env, char *str)
{
	if (needed_first(str[0]) && !ft_after_equ(str, '='))
	{
		ft_lstaddback(env, ft_lst_new(
				ft_substr_env(str, 0, search_lenght(str, '=') - 1), "\0"));
		return (1);
	}
	else if (needed_first(str[0]) && ft_after_equ(str, '='))
	{
		ft_lstaddback(env, ft_lst_new(
				ft_substr_env(str, 0, search_lenght(str, '=') - 1),
				ft_substr_env(str, search_lenght(str, '=') + 1, 
					ft_strlen(str) - search_lenght(str, '='))));
		return (1);
	}
	else
		return (0);
}
