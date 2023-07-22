/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:54:40 by Gecko             #+#    #+#             */
/*   Updated: 2023/07/22 20:19:24 by Gecko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
        char    *tab;
        size_t  malloc_size;
        size_t  i;

        if (start > ft_strlen(s))
                malloc_size = 1;
        else if (!s)
                return (NULL);
        else if (len > ft_strlen(s) - start)
                malloc_size = ft_strlen(s) - start + 1;
        else
                malloc_size = len + 1;
        tab = malloc(malloc_size * sizeof(char));
        if (!tab)
                return (NULL);
        i = 0;
        while (malloc_size - 1 && s[i])
        {
                tab[i] = *(s + start);
                start++;
                malloc_size--;
                i++;
        }
        tab[i] = '\0';
        return (tab);
}
