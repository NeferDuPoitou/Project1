/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 10:31:04 by Gecko             #+#    #+#             */
/*   Updated: 2023/07/16 14:05:27 by Gecko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char *p_dest;
	const char *p_src;

	p_dest = dest;
	p_src = src;
	while (n--)
	{
		*p_dest = *p_src;
		p_dest++;
		p_src++;
	}
	return (dest);
}
