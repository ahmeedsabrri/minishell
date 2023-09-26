/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 01:44:30 by asabri            #+#    #+#             */
/*   Updated: 2023/09/25 22:10:59 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_none_expand(char *str, int *index)
{
	int		i;
	char	*ptr;

	i = *index;
	while (str[i] && str[i] != '$')
		i++;
	ptr = ft_substr(str, *index, i - *index);
	*index = i - 1;
	return (ptr);
}

char	*check_expand(char *str, t_env *env, int *i)
{
	int		index;
	char	*var;

	(void)env;
	index = *i + 1;
	if (str[index] == 0)
		return ("$");
	if (str[index] && str[index] == '?')
	{
		*i = index;
		return (ft_itoa(g_global_exit));
	}
	if (str[index] && (str[index] == '_' || ft_isalpha(str[index])))
		index++;
	while (str[index] && (str[index] == '_' || ft_isalnum(str[index])))
		index++;
	var = ft_substr(str, *i + 1, index - *i - 1);
	*i = index - 1;
	while (env)
	{
		if (!ft_strcmp(env->var, var))
			return (ft_strdup(env->val));
		env = env->next;
	}
	return (NULL);
}

char	**ft_expand(char *str, t_env *env, int mode)
{
	char	*ptr;
	char	*cmd;
	char	**s;
	int		i;

	cmd = NULL;
	ptr = NULL;
	i = -1;
	s = ft_malloc(sizeof(char *) * 2, 1);
	while (str[++i])
	{
		if (str[i] == '$')
			ptr = check_expand(str, env, &i);
		else
			ptr = check_none_expand(str, &i);
		cmd = ft_strjoin(cmd, ptr);
	}
	free(str);
	if (mode == 1)
		return (ft_split(cmd, ' '));
	return (s[0] = ft_malloc(sizeof(char) * ft_strlen(cmd) + 1, 1),
		s[0] = ft_strdup(cmd), s[1] = NULL, s);
}
