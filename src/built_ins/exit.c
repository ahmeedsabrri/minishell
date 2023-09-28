/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:46:36 by yamajid           #+#    #+#             */
/*   Updated: 2023/09/28 12:07:59 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

long long	ft_atoi_long(const char *str)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * sign);
}

int	check_str_error(char *str)
{
	int	i;

	i = 0;
	while (str[i++])
		if ((str[i] <= 'a' && str[i] >= 'z')
			|| (str[i] <= 'A' && str[i] >= 'Z')) 
			return (0);
	return (1);
}

int	check_num_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

void	exit_built(int argc, char **argv)
{
	if (argc == 1)
	{
		printf("exit\n");
		exit(g_global_exit);
	}
	else if (argc > 2 && (check_str_error(argv[1]) == 1 
			|| check_num_error(argv[1]) == 1))
	{
		if (check_num_error(argv[1]) == 1)
		{
			printf("bash: exit: too many arguments\n");
			_status(1);
		}
		else
		{
			printf("bash: exit: %s: numeric argument required\n", argv[1]);
			exit(255);
		}
	}
	else
	{
		_status(ft_atoi_long(argv[1]));
		exit(g_global_exit);
	}
}
