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

static size_t	calculate_SIZE_MAX() {
	// Determine the size of size_t in bytes
	size_t size_t_size = 0;
	size_t temp = ~(size_t)0;

	while (temp != 0) 
	{
		temp >>= 8;
		size_t_size++;
	}
	// Create the SIZE_MAX value without directly using SIZE_MAX or any other standard header
	size_t size_max = 0;
	for (size_t i = 0; i < size_t_size; i++) 
	{
		size_max <<= 8;
		size_max |= 0xFF;
	}
	return size_max;
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
        size_t	total_size;
	size_t	size_max;

	total_size = nmemb * size;
	size_max = calculate_SIZE_MAX();
	if (size != 0)
	{
		if (nmemb > size_max / size)
			return (NULL);
	}
	if ((nmemb == 0 && size != 0) || (nmemb == 0 && size == 0)\
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

