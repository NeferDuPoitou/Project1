/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 10:26:48 by Gecko             #+#    #+#             */
/*   Updated: 2023/07/18 18:14:06 by Gecko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	
	i = 0;
	if (little[0] == '\0')
		return ((char*)big);
	while (big[i] && i < len - 1)
	{
		j = 0;
		while (big[i] == little[j] && i < len - 1)
		{
			if (j == ft_strlen(little) - 1)
				return ((char*)&big[i - ft_strlen(little) + 1]);
			i++;
			j++;
		}
		i++;
	}
	return (NULL);
}
