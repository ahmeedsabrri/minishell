/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 03:30:08 by asabri            #+#    #+#             */
/*   Updated: 2023/09/21 04:10:43 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1,int len)
{
	char	*p;
	
	p = malloc((sizeof(char) * (len + 1)));
	if (!p)
		return (NULL);
	p[len] = '\0';
	len--;
	while (len >= 0)
	{
		p[len] = s1[len];
		len--;
	}
	return (p);
}

char	*ft_strdup(const char *s1)
{
	char	*p;
	int		len;

	len = 0;
	if (!s1)
		return ("");
	while (s1[len])
		len++;
	p = ft_malloc((sizeof(char) * (len + 1)), 1);
	if (!p)
		return (NULL);
	p[len] = '\0';
	while (len >= 0)
	{
		p[len] = s1[len];
		len--;
	}
	return (p);
}

char	*ft_strdup_env(const char *s1)
{
	char	*p;
	int		len;

	len = 0;
	if (!s1)
		return (NULL);
	while (s1[len])
		len++;
	p = malloc((sizeof(char) * (len + 1)));
	if (!p)
		return (NULL);
	p[len] = '\0';
	while (len >= 0)
	{
		p[len] = s1[len];
		len--;
	}
	return (p);
}