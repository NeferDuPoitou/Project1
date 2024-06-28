/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlist_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:54:37 by achatzit          #+#    #+#             */
/*   Updated: 2024/03/15 12:54:40 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

t_mlist	*mlistnew(void *content, int is_critical)
{
	t_mlist	*node;

	node = malloc(1 * sizeof(t_mlist));
	if (!node)
	{
		free(content);
		ft_putstr_fd("Malloc fail mlistnew\n", 2);
		wclear(1);
		exit(1);
	}
	node->c = content;
	node->critical = is_critical;
	node->next = NULL;
	return (node);
}

void	mlistadd_front(t_mlist **lst, t_mlist *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

t_mlist	*mlistlast(t_mlist *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
		lst = lst->next;
	return (lst);
}

void	mlistadd_back(t_mlist **lst, t_mlist *new)
{
	t_mlist	*last;

	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			last = mlistlast(*lst);
			last->next = new;
		}
	}
}

void	free_mlistnode(t_mlist *to_del)
{
	free(to_del->c);
	free(to_del);
}
