/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 10:33:31 by Gecko             #+#    #+#             */
/*   Updated: 2023/07/16 14:04:29 by Gecko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p_src;
	unsigned char		ch;

	p_src = s;
	ch = c;
	while (n--)
	{
		if (*p_src == ch)
			return (void*)p_src;
		p_src++;
	}
	return (NULL);
}
