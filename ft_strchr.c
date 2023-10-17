/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 10:18:20 by Gecko             #+#    #+#             */
/*   Updated: 2023/07/18 11:20:50 by Gecko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (c > 256)
		c = c - 256;
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
