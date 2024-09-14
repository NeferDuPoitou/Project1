#include "../libft.h"
#include <errno.h>

t_lst	*newlst(int is_critical, void (*delf)(void *c), \
				void *(*dupf)(t_lnode *))
{
	t_lst	*new;

	new = walloc(sizeof(t_lst), is_critical);
	if (!new)
		return (errno = ENOMEM, NULL);
	new->head = NULL;
	new->tail = NULL;
	new->size = 0;
	new->alloc_level = is_critical;
	new->delf = delf;
	new->dupf = dupf;
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
