/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:52:01 by yamajid           #+#    #+#             */
/*   Updated: 2023/09/28 11:33:20 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_duplicate(char *arg, t_env *env)
{
	return (check_dupl(ft_cut(arg, '='), env) || ft_search_for_plus(arg, '+'));
}

void	handle_plus(t_env **env, char *arg)
{
	if (ft_search_for_plus(arg, '+'))
		change_value_for_plus(env, arg);
	else if (!ft_stchr(arg, '=') && check_dupl(ft_cut(arg, '='), *env)) 
		wrong();
	else if (!ft_after_equ(arg, '='))
		change_value_if_not(env, ft_cut(arg, '='));
	else if (ft_after_equ(arg, '='))
		change_value_if_exist(env, arg);
}

int	invalid_option(char **argv)
{
	if (argv[1] && argv[1][0] == '-' && argv[1][1]) 
	{
		printf("minishell: export: %s : invalid option\n", argv[1]);
		_status(2);
		return (1);
	}
	return (0);
}

void	no_equal(char **argv, int i, t_env **env)
{
	if (if_error(argv[i]) == 1 && check_string(argv[i]) == 1)
		ft_lstaddback(env, ft_lst_new(ft_strdup_env(argv[i]), NULL));
	else
	{
		printf("minishell: export: '%s': not a valid identifier\n", argv[i]);
		_status(2);
	}
	return ;
}

void	other_cases(char **argv, int i, t_env **env)
{
	if (needed_first(argv[i][0]) && !ft_stchr(argv[i], '='))
		no_equal(argv, i, env);
	else if (needed_first(argv[i][0]) && !ft_after_equ(argv[i], '='))
		ft_lstaddback(env, ft_lst_new(ft_substr_env(argv[i],
					0, search_lenght(argv[i], '=')), "\0"));
	else if (ft_stchr(argv[i], '=') 
		&& needed_first(argv[i][0]) && ft_after_equ(argv[i], '=')) 
	{
		ft_lstaddback(env, ft_lst_new(ft_substr_env(argv[i],
					0, search_lenght(argv[i], '=')),
				ft_substr_env(argv[i], search_lenght(argv[i], '=') + 1,
					ft_strlen(argv[i]) - search_lenght(argv[i], '='))));
	}
	else
		return ;
}
