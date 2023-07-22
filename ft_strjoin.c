/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 09:30:54 by Gecko             #+#    #+#             */
/*   Updated: 2023/07/22 13:57:13 by Gecko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strjoin(char const *s1, char const *s2)
{
        char    *tab;
        size_t  total_size;

        total_size = ft_strlen(s1) + ft_strlen(s2) + 1;
        tab = malloc((total_size) * sizeof(char));
        if (!tab)
                return (NULL);
        tab[0] = '\0';
        ft_strlcat(tab, s1, total_size);
        ft_strlcat(tab, s2, total_size);
        return (tab);
}
