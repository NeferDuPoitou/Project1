/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <achatzit@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 05:24:42 by achatzit          #+#    #+#             */
/*   Updated: 2024/09/16 05:24:44 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <errno.h>

t_lst	*lst_dupn(t_lst *l, t_lnode *t, int n)
{
	t_lst	*newl;
	t_lnode	*new_node;

	if (!l || !t || !l->size || n < 0)
		return (errno = EINVAL, NULL);
	if (!n)
		n = l->size;
	newl = newlst(l->alloc_level, l->delf, l->dupf);
	if (!newl)
		return (errno = ENOMEM, NULL);
	while (n-- && t)
	{
		new_node = lstnew(l->dupf(t), t->alloc_level);
		if (!new_node && errno == ENOMEM)
			return (errno = ENOMEM, NULL);
		lstadd_back(newl, new_node);
		t = t->next;
	}
	return (newl);
}

t_lst	*lst_dup(t_lst *l)
{
	t_lst	*newl;

	if (!l || !l->size)
		return (errno = EINVAL, NULL);
	newl = lst_dupn(l, l->head, 0);
	if (!newl && errno == ENOMEM)
		return (errno = ENOMEM, NULL);
	return (newl);
}

void	lst_delone(t_lst *l, t_lnode *d)
{
	if (!l || !d || l->size == 0)
		return ;
	if (d == l->head)
	{
		l->head = d->next;
		if (l->head)
			l->head->prev = NULL;
	}
	else
		d->prev->next = d->next;
	if (d == l->tail)
	{
		l->tail = d->prev;
		if (l->tail)
			l->tail->next = NULL;
	}
	else
		d->next->prev = d->prev;
	l->delf(d->content);
	wfree(d);
	l->size--;
}

void	lst_remove_if(t_lst *l, int (*cond)(t_lnode *))
{
	t_lnode	*i;
	t_lnode	*temp;

	if (!l || !cond || !l->size)
	{
		errno = EINVAL;
		return ;
	}
	i = l->head;
	while (i)
	{
		temp = i->next;
		if (cond(i))
			lst_delone(l, i);
		i = temp;
	}
}

void	lst_do_if(t_lst *l, int (*cond)(t_lnode *), void (*f)(t_lnode *))
{
	t_lnode	*i;

	if (!l || !cond || !f || !l->size)
	{
		errno = EINVAL;
		return ;
	}
	i = l->head;
	while (i)
	{
		if (cond(i))
			f(i);
		i = i->next;
	}
}
