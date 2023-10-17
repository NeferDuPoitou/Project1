/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:58:58 by Gecko             #+#    #+#             */
/*   Updated: 2023/07/20 18:53:50 by Gecko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	calculate_size_max(void)
{
	size_t	size_t_size;
	size_t	size_max;
	size_t	temp;
	size_t	i;

	size_t_size = 0;
	temp = ~(size_t);
	while (temp != 0)
	{
		temp >>= 8;
		size_t_size++;
	}
	size_max = 0;
	while (i < size_t_size)
	{
		size_max <<= 8;
		size_max |= 0xFF;
		i++;
	}
	return (size_max);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*p;
	size_t		total_size;
	size_t		size_max;

	total_size = nmemb * size;
	size_max = calculate_size_max();
	if (size != 0)
	{
		if (nmemb > size_max / size)
			return (NULL);
	}
	if ((nmemb == 0 && size != 0) || (nmemb == 0 && size == 0) \
	|| (nmemb != 0 && size == 0))
	{
		p = malloc(0);
		return (p);
	}
	else if (nmemb != 0 && size == 0)
		return (NULL);
	p = malloc(total_size);
	if (!p)
		return (NULL);
	ft_bzero(p, total_size);
	return (p);
}
