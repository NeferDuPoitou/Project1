/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:51:52 by Gecko             #+#    #+#             */
/*   Updated: 2023/08/06 17:56:58 by Gecko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list  *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
        t_list  *new;
        t_list  *elem;

        if (!lst || !f)
                return (NULL);
        new = NULL;
        while (lst)
        {
                elem = ft_lstnew(f(lst->content));
                if (!elem)
                {
                        ft_lstclear(&new, del);
                        return (NULL);
                }
                ft_lstadd_back(&new, elem);
                lst = lst->next;
        }
        return (new);
}
