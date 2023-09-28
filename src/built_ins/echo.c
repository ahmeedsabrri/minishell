/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:32:41 by yelwadou          #+#    #+#             */
/*   Updated: 2023/09/28 02:23:09 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_need(char c)
{
  if (c == '-') return (0);
  return (1);
}
int ft_check_arg(char *str)
{
  int i;

  i = 1;
  if (!str)
	return (0);
  while (str[i] != '\0')
  {
    if (str[i] != 'n')
        return (0);
      i++;
  }
  return (1);
}

void ft_echo_case_1(char **argv, int i, int argc)
{
	while (i < argc && (ft_check_arg(argv[i]) == 1 && (ft_need(argv[i][0]) == 0)))
			i++;
    while (i < argc)
    {
			if (i + 1 == argc)
				ft_putstr_fd(argv[i], STDOUT_FILENO);
			else
			{
				ft_putstr_fd(argv[i], STDOUT_FILENO);
				ft_putchar_fd(' ', STDOUT_FILENO);
			}
			i++;
    }
}

void ft_echo_case_2(char **argv, int i, int argc)
{
	while (i < argc && (ft_check_arg(argv[i]) == 1 && (ft_need(argv[i][0]) == 0)))
			i++;
	while (i < argc)
    {
			if (i + 1 == argc)
				ft_putstr_fd(argv[i], STDOUT_FILENO);
			else
			{
				ft_putstr_fd(argv[i], STDOUT_FILENO);
				ft_putchar_fd(' ', STDOUT_FILENO);
			}
			i++;
    }
}
int  echo_no_arg(char **argv, int i)
{
	if (argv[0] && !argv[1])
	{
    	printf("\n");
		return (0);
	}
	else if (argv[0] && ft_check_arg(argv[i]) == 1 && !argv[2])
		return (0);
	else
		return (1);
}
void echo(int argc, char **argv)
{
    int i;
	int flag;

    i = 1;
	flag = 0;
    if (echo_no_arg(argv, i) == 0)
	{
		printf("%s\n", argv[1]);
		return ;
	}
	if ((ft_need(*argv[1]) == 0 && ft_check_arg(argv[1]) == 1))
	{
		i = 2;
		flag = 1;
		ft_echo_case_1(argv, i, argc);
	}
	else
	{
		flag = 0;
		ft_echo_case_2(argv, i, argc);
	}	
	if (flag == 0)
		printf("\n");
	_status(0);
	return ;
}