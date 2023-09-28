/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:51:58 by yamajid           #+#    #+#             */
/*   Updated: 2023/09/28 11:40:00 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_value_for_plus(t_env **env, char *str)
{
	t_env	*ptr;

	ptr = *env;
	while (ptr)
	{
		if (ft_strcmp(ptr->var, ft_cut(str, '+')) == 0)
		{
			if (!ft_after_equ(str, '=') && ptr->val == NULL)
				ptr->val = ft_strdup_env("");
			else if (ft_after_equ(str, '=') && ptr->val == NULL)
				ptr->val = ft_substr_env(str, search_lenght(str, '=') + 1,
						ft_strlen(str) - search_lenght(str, '='));
			else if (ft_after_equ(str, '=') && (!ptr->val[0] || ptr->val[0]))
				ptr->val = ft_strjoin_env(ptr->val, ft_substr_env(str, 
							search_lenght(str, '=') + 1,
							ft_strlen(str) - search_lenght(str, '=')));
			return ;
		}
		ptr = ptr->next;
	}
	if (for_plus(env, str) == 0)
		return ;
}

int	if_error(char *str)
{
	if (((str[ft_strlen(str) - 1] == '_' ) || 
			ft_isalnum(str[ft_strlen(str) - 1])))
		return (1);
	return (0);
}

int	check_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
		{
			if ((str[i] == '+' && str[i + 1] == '=' ) || str[i] == '=')
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

void	wrong(void)
{
	return ;
}

int	validate_arg(char *arg)
{
	return (needed_first(arg[0]) && 
		check_string(ft_cut(arg, search_lenght(arg, '=') - 1)));
}
