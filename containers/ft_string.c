/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <achatzit@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 05:24:59 by achatzit          #+#    #+#             */
/*   Updated: 2024/09/16 05:25:02 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_string	*string_init(char *init, int alloc_lvl)
{
	t_string	*s;
	size_t		len;

	s = walloc(sizeof(t_string), alloc_lvl);
	if (!init || !ft_strlen(init))
	{
		s->capacity = 50;
		s->data = walloc(50, alloc_lvl);
		s->alloc_lvl = alloc_lvl;
		s->len = 0;
		s->cstr = NULL;
		return (s);
	}
	s->cstr = NULL;
	len = ft_strlen(init);
	s->capacity = ft_strlen(init) * 2;
	s->data = walloc(s->capacity, alloc_lvl);
	ft_memmove(s->data, init, len);
	s->len = len;
	s->alloc_lvl = alloc_lvl;
	return (s);
}

void	add_capacity(t_string *s)
{
	void	*newdata;

	newdata = walloc(s->capacity * 2, s->alloc_lvl);
	s->capacity = s->capacity * 2;
	ft_memcpy(newdata, s->data, s->len);
	wfree(s->data);
	s->data = newdata;
}
