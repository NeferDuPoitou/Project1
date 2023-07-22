/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 22:23:08 by Gecko             #+#    #+#             */
/*   Updated: 2023/07/22 22:26:08 by Gecko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
        char    *tab;
        int     i;

        i = 0;
        tab = ft_strdup(s);
        if (!tab)
                return (NULL);
        while (tab[i])
        {
                tab[i] = f(i, s[i]);
                i++;
        }
        return (tab);
}
