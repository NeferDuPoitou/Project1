#include "../libft.h"
#include <errno.h>

void	lst_do_while(t_lst *l, int (*cond)(t_lnode *), void (*f)(t_lnode *))
{
	t_lnode	*i;

	if (!l || !cond || !f || !l->size)
	{
		errno = EINVAL;
		return ;
	}
	i = l->head;
	while (i && cond(i))
	{
		f(i);
		i = i->next;
	}
}

void	lstclear(t_lst **l)
{
	t_lnode	*tmp;

	if (!*l)
	{
		errno = EINVAL;
		return ;
	}
	while ((*l)->head)
	{
		tmp = (*l)->head->next;
		(*l)->delf((*l)->head->content);
		wfree((*l)->head);
		(*l)->head = tmp;
	}
	(*l)->head = NULL;
	(*l)->tail = NULL;
	(*l)->size = 0;
	wfree(*l);
	*l = NULL;
}

void	lstiter(t_lst *l, void (*f)(t_lnode *))
{
	t_lnode	*i;

	if (!l || !f || !l->size)
	{
		errno = EINVAL;
		return ;
	}
	i = l->head;
	while (i)
	{
		f(i);
		i = i->next;
	}
}

void	lstiter_reverse(t_lst *l, void (*f)(t_lnode *))
{
	t_lnode	*i;

	if (!l || !f || l->size)
	{
		errno = EINVAL;
		return ;
	}
	i = l->tail;
	while (i)
	{
		f(i);
		i = i->prev;
	}
}

t_lst	*lstmap(t_lst *l, void (*f)(t_lnode *))
{
	t_lst	*newl;

	if (!l || !f || !l->size)
		return (errno = EINVAL, NULL);
	newl = lst_dup(l);
	if (!newl && errno == ENOMEM)
		return (errno = ENOMEM, NULL);
	lstiter(newl, f);
	return (newl);
}
