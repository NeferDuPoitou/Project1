/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 10:26:48 by Gecko             #+#    #+#             */
/*   Updated: 2023/07/22 22:37:35 by Gecko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	pos;
	int	i;

	if (!*little)
		return ((char *)big);
	pos = 0;
	while (big[pos] && (size_t)pos < len)
	{
		if (big[pos] == little[0])
		{
			i = 1;
			while (little[i] && big[pos + i] == little[i]
				&& (size_t)(pos + i) < len)
				i++;
			if (little[i] == '\0')
				return ((char *)&big[pos]);
		}
		pos++;
	}
	return (NULL);
}
