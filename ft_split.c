/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:47:05 by Gecko             #+#    #+#             */
/*   Updated: 2023/07/22 13:49:29 by Gecko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_char_pointer_pointer_malloc_size(char const *s, char c)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			size++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (size + 1);
}

/* i : string à decouper | k : tableau | j : char */

static int	get_segment_size(char const *s, char c, int *index)
{
	int	size;

	size = 0;
	while (s[*index] == c && s[*index])
		(*index)++;
	while (s[*index] != c && s[*index])
	{
		size++;
		(*index)++;
	}
	return (size);
}

static char	**split_motherfuckers(char **splitted, char const *s, char c)
{
	int	i;
	int	j;
	int	k;
	int	size;

	i = 0;
	k = 0;
	while (s[i])
	{
		size = get_segment_size(s, c, &i);
		if (s[i] == '\0' && s[i - 1] == c)
		{
			splitted[k] = 0;
			return (splitted);
		}
		splitted[k] = malloc((size + 1) * sizeof(char));
		if (!splitted[k])
			return (NULL);
		j = -1;
		while (++j < size)
			splitted[k][j] = s[i - size + j];
		splitted[k++][j] = '\0';
	}
	splitted[k] = 0;
	return (splitted);
}

char	**ft_split(char const *s, char c)
{
	char	**splitted;
	int		pp_size;

	pp_size = get_char_pointer_pointer_malloc_size(s, c);
	splitted = malloc(pp_size * sizeof(char *));
	split_motherfuckers(splitted, s, c);
	if (!splitted)
		return (NULL);
	return (splitted);
}
