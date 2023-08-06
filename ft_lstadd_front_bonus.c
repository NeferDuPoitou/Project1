/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddfront_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:49:25 by Gecko             #+#    #+#             */
/*   Updated: 2023/08/06 17:55:25 by Gecko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_lstadd_front(t_list **lst, t_list *new)
{
        if (lst && new)
        {
                new->next = *lst; // on bouge le pointeur lst (head)
                *lst = new; // et on lui met de la data
        }
}
