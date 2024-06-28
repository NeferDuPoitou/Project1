/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:54:37 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/14 14:44:18 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "stdio.h"

static t_mlist	*find_ptr(t_mlist *allocs, void *ptr)
{
	t_mlist	*tmp;

	tmp = allocs;
	while (tmp)
	{
		if (tmp->c == ptr)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	allocator_print_size(t_mlist *allocs)
{
	size_t			bsize;
	t_mlist			*tmp;

	tmp = allocs;
	bsize = 0;
	while (tmp)
	{
		bsize += sizeof(tmp->c);
		tmp = tmp->next;
	}
	printf("allocator size : %zu\n", bsize);
}

void	*allocator_alloc_new(t_mlist **allocs, int size, int is_critical)
{
	void			*newptr;
	t_mlist			*newnode;

	newptr = malloc(size);
	if (!newptr)
	{
		ft_putstr_fd("Malloc fail mlistnew\n", 2);
		wclear(1);
		exit(1);
	}
	newnode = mlistnew(newptr, is_critical);
	if (!newnode)
	{
		ft_putstr_fd("Malloc fail mlistnew\n", 2);
		free(newptr);
		wclear(1);
		exit(1);
	}
	mlistadd_back(allocs, newnode);
	return (newptr);
}

void	allocator_free(t_mlist **allocs, void *ptr)
{
	t_mlist	*newnode;

	if (ptr)
	{
		newnode = find_ptr(*allocs, ptr);
		if (newnode)
			mlist_delone(allocs, newnode);
	}
}

void	*allocator(int size, int type, void *ptr, int is_critical)
{
	static t_mlist	*allocs;

	if (type == ALLOC)
		return (allocator_alloc_new(&allocs, size, is_critical));
	else if (type == FREE)
		allocator_free(&allocs, ptr);
	else if (type == CLEAR)
		mlist_clear(&allocs, is_critical);
	else if (type == PRINT_SIZE)
		allocator_print_size(allocs);
	return (NULL);
}
