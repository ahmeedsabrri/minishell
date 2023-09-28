/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:51:36 by yamajid           #+#    #+#             */
/*   Updated: 2023/09/28 11:44:59 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_stchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i++]) 
		if (s[i] == c) 
			return (1);
	return (0);
}

int	search_lenght(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i]) 
	{
		if (s[i] == c) 
			return (i);
		i++;
	}
	return (i);
}

int	ft_after_equ(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i++])
		if (str[i] == c) 
			if (str[i + 1] != '\0') 
				return (1);
	return (0);
}

int	check_dupl(char *str, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if ((ft_strcmp(tmp->var, str) == 0))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	search_after_equ(char *str)
{
	int	i;

	i = 0;
	while (str[i++])
		if (str[i] == '=' && str[i + 1] == '\0')
			return (1);
	return (0);
}
