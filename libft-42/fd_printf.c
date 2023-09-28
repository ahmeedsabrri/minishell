/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 02:28:50 by asabri            #+#    #+#             */
/*   Updated: 2023/09/28 09:25:52 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

void	fd_printf(int fd, const char *fmt, ...)
{
	int		i;
	va_list	s;

	i = -1;
	va_start(s, fmt);
	if (!fmt)
	{
		// printf("");
		return ;
	}
	while (fmt[++i])
	{
		if (fmt[i] != '%')
		{
			write(fd, &fmt[i], 1);
		}
		if (fmt[i] == '%' && fmt[i + 1])
		{
			if (fmt[i + 1] == 's')
				ft_putstr_fd(va_arg(s, char *), fd);
			else if (fmt[i + 1] == 'd')
				ft_putnbr_fd(va_arg(s, int), fd);
			else
				write(fd, &fmt[i + 1], 1);
			i++;
		}
	}
}