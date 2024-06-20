#include "../libft.h"
#include <errno.h>


t_lst	*newlst(int is_critical)
{
	t_lst	*new;

	new = walloc(sizeof(t_lst), is_critical);
	if (!new)
		return (errno = ENOMEM, NULL);
	new->head = NULL;
	new->tail = NULL;
	new->size = 0;
	new->alloc_level = is_critical;
	return (new);
}

t_lnode	*lstnew(void *content, int is_critical)
{
	t_lnode	*new;

	if (!content)
		return (errno = EINVAL, NULL);
	new = walloc(sizeof(t_lnode), is_critical);
	if (!new)
		return (errno = ENOMEM, NULL);
	new->next = NULL;
	new->prev = NULL;
	new->content = content;
	new->alloc_level = is_critical;
	return (new);
}

void	lstadd_front(t_lst *l, t_lnode *new)
{
	if (!new || !l)
	{
		errno = EINVAL;
		return ;
	}
	new->next = l->head;
	if (l->head)
		l->head->prev = new;
	l->head = new;
	if (!l->tail)
		l->tail = new;
	l->size++;
}

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

void	lst_replace(t_lst *l, t_lnode *t, t_lnode *new, void (*del)(void *c))
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
	del(t->content);
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
	t_lnode *i;

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

t_lst	*lst_dupn(t_lst *l, t_lnode *t, int n, void *(*dupf)(t_lnode *))
{
	t_lst	*newl;
	t_lnode	*new_node;

	if (!l || !t || !dupf || !l->size || n < 0)
		return (errno = EINVAL, NULL);
	if (!n)
		n = l->size;
	newl = newlst(l->alloc_level);
	if (!newl)
		return (errno = ENOMEM, NULL);
	while (n-- && t)
	{
		new_node = lstnew(dupf(t), t->alloc_level);
		if (!new_node && errno == ENOMEM)
			return (errno = ENOMEM, NULL);
		lstadd_back(newl, new_node);
		t = t->next;
	}
	return (newl);
}

t_lst	*lst_dup(t_lst *l, void *(dupf)(t_lnode *))
{
	t_lst	*newl;

	if (!l || !dupf || !l->size)
		return (errno = EINVAL, NULL);
	newl = lst_dupn(l, l->head, 0, dupf);
	if (!newl && errno == ENOMEM)
		return (errno = ENOMEM, NULL);
	return (newl);
}

void	lst_delone(t_lst *l, t_lnode *d, void (*del)(void *c))
{
	if (!l || !d || l->size == 0)
		return;
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
	del(d->content);
	wfree(d);
	l->size--;
}

void	lst_remove_if(t_lst *l, int (*cond)(t_lnode *), void (*del)(void *c))
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
			lst_delone(l, i, del);
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

void	lstclear(t_lst *l, void (*del)(void *c))
{
	t_lnode	*tmp;

	if (!l)
	{
		errno = EINVAL;
		return ;
	}
	while (l->head)
	{
		tmp = l->head->next;
		del(l->head->content);
		wfree(l->head);
		l->head = tmp;
	}
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
}

void	lstiter(t_lst *l, void (*f)(t_lnode *))
{
	t_lnode *i;

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
	t_lnode *i;

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

t_lst	*lstmap(t_lst *l, void (*f)(t_lnode *), void* (*dupf)(t_lnode *))
{
	t_lst	*newl;

	if (!l || !f || !dupf || !l->size)
		return (errno = EINVAL, NULL);
	newl = lst_dup(l, dupf);
	if (!newl && errno == ENOMEM)
		return (errno = ENOMEM, NULL);
	lstiter(newl, f);
	return (newl);
}

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

t_lst	*lst_split_at_deep(t_lst *l, \
							t_lnode *t, \
							void *(*dupf)(t_lnode *), \
							void (*del)(void *c))
{
	t_lst	*newl;
	t_lnode	*tmp;

	if (!l || !t || t == l->head || t == l->tail || !l->size)
		return (errno = EINVAL, NULL);
	l->tail = t->prev;
	t->prev->next = NULL;
	t->prev = NULL;
	newl = lst_dupn(l, t, 0, dupf);
	if (!newl && errno == ENOMEM)
		return (errno = ENOMEM, NULL);
	while (t)
	{
		tmp = t->next;
		del(t->content);
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
	newl = newlst(l->alloc_level);
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

#ifdef LSTTEST

/*============*/
/*testing area*/
/*============*/

#include <string.h>
#include <stdio.h>

/* function pointers */

static void	print_node(t_lnode *n)
{
	printf("%s\n", (char *)n->content);
}

static void	sixsixsix(t_lnode *n)
{
	wfree(n->content);
	n->content = ft_itoa(666, SAFE);
}

static void	*copy_str(t_lnode *n)
{
	return (ft_strdup(n->content, n->alloc_level));
}

static void	plusone(t_lnode *n)
{
	int nb = ft_atoi(n->content);
	nb++;
	wfree(n->content);
	n->content = ft_itoa(nb, SAFE);
}

static int	removeif(t_lnode *n)
{
	return (ft_atoi(n->content) % 2 == 0);
}

static int	doif(t_lnode *n)
{
	return (ft_atoi(n->content) % 2 == 0);
}

static int	dowhile(t_lnode *n)
{
	return (ft_atoi(n->content) < 5);
}

static void	del(void *c)
{
	wfree(c);
}

int main(void)
{
	t_lst *l = newlst(SAFE);
	for (int i = 0; i < 10; i++)
	{
		t_lnode *n = lstnew(ft_itoa(i, SAFE), SAFE);
		lstadd_back(l, n);
	}
	lstiter(l, &print_node);

	printf("\n");

	t_lst *l2 = lst_split_at_shallow(l, l->head->next->next->next);
	lstiter(l, &print_node);
	printf("\n");
	lstiter(l2, &print_node);
	printf("1 head: %s 1 tail: %s\n2 head: %s 2 tail: %s\n",
		(char *)l->head->content, (char *)l->tail->content,
		(char *)l2->head->content, (char *)l2->tail->content);
	printf("1 size: %ld 2 size: %ld\n", l->size, l2->size);

	lstclear(l, &del);
	lstclear(l2, &del);
	wfree(l);
	wfree(l2);
	// wclear(1);
}

#endif
