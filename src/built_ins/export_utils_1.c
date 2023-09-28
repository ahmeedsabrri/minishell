/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 07:14:17 by yamajid           #+#    #+#             */
/*   Updated: 2023/09/28 12:13:17 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_lst_size(t_env *env)
{
	int	i;

	i = 0;
	if (!env)
		return (i);
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

int	needed_first(char c)
{
	if (((c == '_' ) || ft_isalpha(c)))
		return (1);
	return (0);
}

t_env	*ft_lst_last(t_env *env)
{
	if (env->next == NULL)
		return (env);
	while (env->next)
		env = env->next;
	return (env);
}

t_env	*ft_lst_new(char *str, char *val)
{
	t_env	*head;

	head = (t_env *)ft_malloc(sizeof(t_env), 2);
	if (!head)
		return (NULL);
	head->var = str;
	if (val == NULL)
		head->val = NULL;
	else
		head->val = val;
	head->next = NULL;
	return (head);
}

void	ft_lstaddback(t_env **env, t_env *newnode)
{
	t_env	*lastnode;

	if (!env || !newnode)
		return ;
	if (!*env)
	{
		*env = newnode;
		return ;
	}
	lastnode = ft_lst_last(*env);
	lastnode->next = newnode;
}
