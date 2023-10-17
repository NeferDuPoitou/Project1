/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 10:31:39 by Gecko             #+#    #+#             */
/*   Updated: 2023/07/18 10:58:42 by Gecko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*p_dest;
	const char	*p_src = src;
	char		p_temp[n];
	size_t		i;

	i = 0;
	p_dest = dest;
	while (i < n)
	{
		p_temp[i] = p_src[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		p_dest[i] = p_temp[i];
		i++;
	}
	return (dest);
}
