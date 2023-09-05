/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 00:35:29 by asabri            #+#    #+#             */
/*   Updated: 2023/09/01 07:20:53 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if(!s)
		return(write(fd, "(null)", 6), (void)0);
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}
