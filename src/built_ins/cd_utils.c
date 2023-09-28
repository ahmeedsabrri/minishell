/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:57:16 by asabri            #+#    #+#             */
/*   Updated: 2023/09/28 12:04:36 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_home_path(t_env **env)
{
	char	*str;
	t_env	*ptr;

	str = NULL;
	ptr = *env;
	while (ptr)
	{
		if (ft_strcmp(ptr->var, "HOME") == 0)
		{
			str = ft_malloc(sizeof(ptr->val), 2);
			if (!str)
				return (NULL);
			str = ptr->val;
		}
		ptr = ptr->next;
	}
	return (str);
}

void	set_env_var(t_env **env, char *key, char *value)
{
	t_env	*head;

	head = *env;
	if (head == NULL)
		return ;
	while (head) 
	{
		if (ft_strcmp((head)->var, key) == 0) 
		{
			(head)->val = NULL;
			(head)->val = ft_strdup_env(value);
			return ;
		}
		head = head->next;
	}
}

char	*get_env_var(t_env **env, char *key)
{
	if (env == NULL) 
		return (NULL);
	while (*env)
	{
		if (ft_strcmp((*env)->var, key) == 0)
			return ((*env)->val);
		env = &(*env)->next;
	}
	return (NULL);
}

void	ft_add_to_val(t_env **env, char *key)
{
	if (env == NULL)
		return ;
	while (*env) 
	{
		if (ft_strcmp((*env)->var, key) == 0) 
		{
			(*env)->val = ft_strjoin_env((*env)->val, "/..");
			return ;
		}
		env = &(*env)->next;
	}
}

void	update_pwd(t_env **env, char **argv)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*n_pwd;

	old_pwd = get_env_var(env, "PWD"); 
	if (old_pwd)
		set_env_var(env, "OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
		set_env_var(env, "PWD", new_pwd);
	else
	{
		n_pwd = get_env_var(env, "PWD");
		if (ft_strcmp(argv[1], ".") == 0)
			set_env_var(env, "PWD", ft_strjoin_env(n_pwd, "/."));
		else if (ft_strcmp(argv[1], "..") == 0)
			set_env_var(env, "PWD", ft_strjoin_env(n_pwd, "/.."));
		ft_putstr_fd("cd: error retrieving current directory:\
		getcwd: cannot access parent directories:\
		No such file or directory\n", STDOUT_FILENO);
	}
}
