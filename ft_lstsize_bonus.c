/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:49:56 by Gecko             #+#    #+#             */
/*   Updated: 2023/08/06 17:55:35 by Gecko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_lstsize(t_list *lst)
{
        int     len;

        len = 0;
        while (lst)
        {
                len++;
                lst = lst->next;
        }
        return (len);
}
