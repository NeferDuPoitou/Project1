/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <achatzit@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 05:25:24 by achatzit          #+#    #+#             */
/*   Updated: 2024/09/16 05:25:25 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <errno.h>
#include <stdio.h>

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size, int alloc_lvl)
{
	void	*newptr;

	if (!ptr)
		return (walloc(new_size, alloc_lvl));
	if (!new_size && ptr)
		return (wfree(ptr), NULL);
	newptr = walloc(new_size, alloc_lvl);
	if (!newptr)
		return (errno = ENOMEM, NULL);
	ft_memcpy(newptr, ptr, old_size);
	wfree(ptr);
	return (newptr);
}
