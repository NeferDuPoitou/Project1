/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <achatzit@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 05:25:11 by achatzit          #+#    #+#             */
/*   Updated: 2024/09/16 05:25:12 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdarg.h>

size_t	string_append(t_string *s, t_string *to_append)
{
	size_t	i;

	i = 0;
	while (i < to_append->len)
	{
		if (s->len == s->capacity)
			add_capacity(s);
		s->data[s->len] = to_append->data[i];
		s->len++;
		i++;
	}
	return (i);
}

size_t	string_prepend(t_string *s, t_string *to_prepend)
{
	size_t	i;

	i = 0;
	while (i < to_prepend->len)
	{
		if (s->len + 2 >= s->capacity)
			add_capacity(s);
		ft_memmove(&s->data[i + 1], &s->data[i], s->len++);
		s->data[i] = to_prepend->data[i];
		i++;
	}
	return (i);
}

static void	fmtf(const char *fmt, t_string *s, va_list *arg, char *tmp)
{
	if (*fmt && *fmt == '%' && *(fmt + 1) && \
		*(fmt + 1) == 't' && *(fmt + 2) && *(fmt + 2) == 's')
	{
		string_append(s, va_arg(*arg, t_string *));
		fmt += 3;
	}
	else if (*fmt && *fmt == '%' && *(fmt + 1) && *(fmt + 1) == 's')
	{
		string_append_cstr(s, va_arg(*arg, char *));
		fmt += 2;
	}
	else if (*fmt && *fmt == '%' && *(fmt + 1) && *(fmt + 1) == 'd')
	{
		tmp = ft_itoa(va_arg(*arg, int), s->alloc_lvl);
		string_append_cstr(s, tmp);
		wfree(tmp);
		fmt += 2;
	}
	else if (*fmt)
	{
		if (s->len >= s->capacity)
			add_capacity(s);
		s->data[s->len++] = *fmt;
		fmt++;
	}
}

void	string_appendfmt(t_string *s, const char *fmt, ...)
{
	va_list	arg;
	char	*tmp;

	tmp = 0;
	va_start(arg, fmt);
	while (*fmt)
	{
		fmtf(fmt, s, &arg, tmp);
	}
	va_end(arg);
}

void	string_append_cstr(t_string *s, const char *cstr)
{
	while (*cstr)
	{
		if (s->len == s->capacity)
			add_capacity(s);
		s->data[s->len++] = *cstr;
		cstr++;
	}
}
