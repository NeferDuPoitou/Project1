/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:43:33 by achatzit          #+#    #+#             */
/*   Updated: 2024/03/15 12:54:43 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	get_size(int nb)
{
	int	size;

	if (nb > 0)
		size = 0;
	else
		size = 1;
	while (nb)
	{
		nb /= 10;
		size++;
	}
	return (size + 1);
}

static void	recursive_itoa(char *tab, long int nb, int *i)
{
	if (nb < 0)
	{
		tab[*i] = '-';
		nb = -nb;
		(*i)++;
	}
	if (nb > 9)
	{
		recursive_itoa(tab, nb / 10, i);
	}
	tab[*i] = nb % 10 + '0';
	(*i)++;
}

char	*ft_itoa(int n, int is_critical)
{
	long int	nb;
	char		*tab;
	int			i;
	int			size;

	i = 0;
	nb = n;
	size = get_size(n);
	tab = walloc(size * sizeof(char), is_critical);
	if (!tab)
		return (NULL);
	recursive_itoa(tab, nb, &i);
	tab[i] = '\0';
	return (tab);
}
