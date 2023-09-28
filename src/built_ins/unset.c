/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:46:10 by yamajid           #+#    #+#             */
/*   Updated: 2023/09/28 11:41:36 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valide_str(char *str)
{
	int	i;
	int	len;

	i = 1;
	len = ft_strlen(str) - 1;
	while (i < len)
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	unset(t_env **env, char **argv, int argc)
{
	int		i;
	t_env	*ptr;
	t_env	*prev;

	i = 1;
	while (i < argc)
	{
		prev = NULL;
		ptr = *env;
		if (needed_first(argv[i][0]) == 0 
			|| if_error(argv[i]) == 0 || !valide_str(argv[i]))
			printf("minishell: unset: `%s': not a valid identifier\n", argv[i]);
		while (ptr)
		{
			if (ft_strcmp(argv[i], ptr->var) == 0)
			{
				if (prev == NULL)
					*env = ptr->next;
				else
					prev->next = ptr->next;
				free(ptr->var);
				if (ptr->val)
					free(ptr->val);
				free(ptr);
				break ;
			}
			prev = ptr;
			ptr = ptr->next;
		}
		i++;
	}
}
