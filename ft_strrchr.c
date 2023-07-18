/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:26:25 by Gecko             #+#    #+#             */
/*   Updated: 2023/07/18 11:29:21 by Gecko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	size;

	if (c > 256)
		c = c - 256;
	size = ft_strlen(s);
	if (c == 0)
		return ((char*)s + size);
	while (size >= 0)
	{
		if (s[size] == c)
			return ((char*)s + size);
		size--;
	}
	return (NULL);
}
