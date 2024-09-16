/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <achatzit@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 05:24:46 by achatzit          #+#    #+#             */
/*   Updated: 2024/09/16 05:24:48 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <errno.h>

void	lstmerge_back(t_lst *l, t_lst *new)
{
	if (!l || !new || !new->size)
	{
		errno = EINVAL;
		return ;
	}
	new->head->prev = l->tail;
	l->tail->next = new->head;
	l->tail = new->tail;
	l->size += new->size;
}

void	lstmerge_after(t_lst *l, t_lnode *t, t_lst *new)
{
	if (!l || !t || !new->size)
	{
		errno = EINVAL;
		return ;
	}
	if (t == l->tail)
	{
		lstmerge_back(l, new);
		return ;
	}
	new->tail->next = t->next;
	new->head->prev = t;
	t->next->prev = new->tail;
	t->next = new->head;
	l->size += new->size;
}

void	lstmerge_before(t_lst *l, t_lnode *t, t_lst *new)
{
	if (!l || !t || !new || !new->size)
	{
		errno = EINVAL;
		return ;
	}
	if (t == l->head)
	{
		lstmerge_front(l, new);
		return ;
	}
	new->tail->next = t;
	new->head->prev = t->prev;
	t->prev->next = new->head;
	t->prev = new->tail;
	l->size += new->size;
}

t_lnode	*lst_find(t_lst *l, void *to_find)
{
	t_lnode	*i;

	if (!l || !to_find)
		return (errno = EINVAL, NULL);
	i = l->head;
	while (i)
	{
		if (!ft_memcmp(to_find, i->content, ft_strlen(to_find)))
			return (i);
		i = i->next;
	}
	return (NULL);
}

t_lnode	*lst_dupnode(t_lnode *node, void *(*dupf)(t_lnode *))
{
	t_lnode	*new;
	void	*newc;

	if (!node || !dupf)
		return (errno = EINVAL, NULL);
	newc = dupf(node);
	new = lstnew(newc, node->alloc_level);
	if (!new)
		return (errno = ENOMEM, NULL);
	new->alloc_level = node->alloc_level;
	return (new);
}
