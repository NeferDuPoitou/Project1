/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlist_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:43:46 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/14 14:43:48 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	mlist_delone(t_mlist **head, t_mlist *to_del)
{
	t_mlist	*tmp;
	t_mlist	*prev;
	t_mlist	*next;

	tmp = *head;
	next = NULL;
	prev = NULL;
	while (tmp)
	{
		if (tmp->next == to_del)
			prev = tmp;
		if (tmp == to_del)
		{
			if (tmp->next)
				next = tmp->next;
			free_mlistnode(to_del);
			if (prev)
				prev->next = next;
			else
				*head = next;
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	return (FAILURE);
}

void	mlist_clear(t_mlist **allocs, int free_critical)
{
	t_mlist	*tmp;
	t_mlist	*tmp2;

	tmp = *allocs;
	while (tmp)
	{
		if ((tmp->critical == CRITICAL && free_critical == 1) \
				|| tmp->critical == SAFE)
		{
			tmp2 = tmp->next;
			wfree(tmp->c);
			wfree(tmp);
			tmp = tmp2;
		}
		else if (tmp->critical == CRITICAL)
		{
			tmp = tmp->next;
		}
	}
}
