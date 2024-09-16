/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <achatzit@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 05:24:33 by achatzit          #+#    #+#             */
/*   Updated: 2024/09/16 05:24:34 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <errno.h>

void	lst_reverse(t_lst *l)
{
	t_lnode	*current;
	t_lnode	*temp;

	if (!l || !l->head || !l->size)
	{
		errno = EINVAL;
		return ;
	}
	current = l->head;
	temp = NULL;
	l->head = l->tail;
	l->tail = current;
	while (current)
	{
		temp = current->next;
		current->next = current->prev;
		current->prev = temp;
		current = current->prev;
	}
}

t_lst	*lst_split_at_deep(t_lst *l, t_lnode *t)
{
	t_lst	*newl;
	t_lnode	*tmp;

	if (!l || !t || t == l->head || t == l->tail || !l->size)
		return (errno = EINVAL, NULL);
	l->tail = t->prev;
	t->prev->next = NULL;
	t->prev = NULL;
	newl = lst_dupn(l, t, 0);
	if (!newl && errno == ENOMEM)
		return (errno = ENOMEM, NULL);
	while (t)
	{
		tmp = t->next;
		l->delf(t->content);
		wfree(t);
		t = tmp;
	}
	l->size -= newl->size;
	return (newl);
}

t_lst	*lst_split_at_shallow(t_lst *l, t_lnode *t)
{
	t_lst	*newl;

	if (!l || !t || t == l->head || t == l->tail || !l->size)
		return (errno = EINVAL, NULL);
	newl = newlst(l->alloc_level, l->delf, l->dupf);
	newl->tail = l->tail;
	newl->head = t;
	l->tail = t->prev;
	t->prev->next = NULL;
	t->prev = NULL;
	newl->size = lstsize(newl);
	l->size -= newl->size;
	return (newl);
}

size_t	lstsize(t_lst *l)
{
	t_lnode	*n;
	size_t	i;

	i = 0;
	n = l->head;
	while (n)
	{
		i++;
		n = n->next;
	}
	return (i);
}

t_lnode	*lstlast(t_lst *l)
{
	t_lnode	*n;

	n = l->head;
	while (n)
		n = n->next;
	return (n);
}
