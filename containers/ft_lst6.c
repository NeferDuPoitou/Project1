#include "../libft.h"
#include <errno.h>

void	lstadd_back(t_lst *l, t_lnode *new)
{
	if (!new)
	{
		errno = EINVAL;
		return ;
	}
	new->prev = l->tail;
	if (l->tail)
		l->tail->next = new;
	l->tail = new;
	if (!l->head)
		l->head = new;
	l->size++;
}

void	lstadd_after(t_lst *l, t_lnode *t, t_lnode *new)
{
	if (!l || !new || !t)
	{
		errno = EINVAL;
		return ;
	}
	if (t == l->tail || !l->size)
	{
		lstadd_back(l, new);
		return ;
	}
	new->next = t->next;
	new->prev = t;
	t->next->prev = new;
	t->next = new;
	l->size++;
}

void	lstadd_before(t_lst *l, t_lnode *t, t_lnode *new)
{
	if (!l || !new || !t)
	{
		errno = EINVAL;
		return ;
	}
	if (t == l->head || !l->size)
	{
		lstadd_front(l, new);
		return ;
	}
	new->next = t;
	new->prev = t->prev;
	t->prev->next = new;
	t->prev = new;
	l->size++;
}

void	lst_replace(t_lst *l, t_lnode *t, t_lnode *new)
{
	if (!l || !t || !new || !l->size)
	{
		errno = EINVAL;
		return ;
	}
	new->next = t->next;
	new->prev = t->prev;
	if (t == l->head)
	{
		t->next->prev = new;
		l->head = new;
	}
	else if (t == l->tail)
	{
		t->prev->next = new;
		l->head = new;
	}
	else
	{
		t->prev->next = new;
		t->next->prev = new;
	}
	l->delf(t->content);
	wfree(t);
}

void	lstmerge_front(t_lst *l, t_lst *new)
{
	if (!l || !new || !new->size)
	{
		errno = EINVAL;
		return ;
	}
	new->tail->next = l->head;
	l->head->prev = new->tail;
	l->head = new->head;
	l->size += new->size;
}
