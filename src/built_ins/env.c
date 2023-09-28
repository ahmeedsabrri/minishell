/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:46:30 by yamajid           #+#    #+#             */
/*   Updated: 2023/09/28 11:19:16 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_env(t_env **env)
{
	t_env	*ptr;

	ptr = *env;
	if (!ptr)
		return ;
	while (ptr)
	{
		if ((ptr)->val)
			printf("%s=%s\n", (ptr)->var, (ptr)->val);
		ptr = (ptr)->next;
	}
	_status(0);
}
