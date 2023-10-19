/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:48:40 by achatzit          #+#    #+#             */
/*   Updated: 2023/10/18 14:48:42 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (c > 256)
		c = c - 256;
	if (*s == 0 && c == 0)
		return (char *)(s);
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		else if (*(s + 1) == c)
			return ((char *)s + 1);
		s++;
	}
	return (NULL);
}
