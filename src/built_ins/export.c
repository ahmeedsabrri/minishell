/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:46:46 by yamajid           #+#    #+#             */
/*   Updated: 2023/09/28 11:29:02 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export(char **argv, t_env **env, int argc)
{
	int	i;

	i = 1;
	if (invalid_option(argv) == 1)
		return (1);
	while (i < argc) 
	{
		if (argv[i] != NULL)
		{
			if (!validate_arg(argv[i]))
			{
				printf("minishell: export: '%s': not a valid identifier\n", 
					argv[i]);
				_status(1);
			}
			else if (is_duplicate(argv[i], *env))
				handle_plus(env, argv[i]);
			else
				other_cases(argv, i, env);
		}
		i++;
	}
	return (1);
}

void	sort_list_for_export(t_env *env)
{
	t_env	*ptr;
	char	*var;
	char	*val;
	int		j;
	int		i;

	ptr = env;
	i = ft_lst_size(env);
	while (--i > 0)
	{
		j = i - 1;
		while (j--)
		{
			if (env->next && ft_strncmp(env->var, env->next->var, 1) > 0)
			{
				var = env->var;
				val = env->val;
				env->var = env->next->var;
				env->val = env->next->val;
				env->next->var = var;
				env->next->val = val;
			}
			env = env->next;
		}
		env = ptr;
	}
}

void	export_alone(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	sort_list_for_export(tmp);
	while (tmp)
	{
		if (!tmp->val)
			printf("declare -x %s\n", tmp->var);
		else
			printf("declare -x %s=\"%s\"\n", tmp->var, tmp->val);
		tmp = tmp->next;
	}
}
