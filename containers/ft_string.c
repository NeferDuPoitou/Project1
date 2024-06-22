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

#include <stdarg.h>
void	string_appendfmt(t_string *s, const char *fmt, ...)
{
	va_list	arg;
	char	*tmp;

	va_start(arg, fmt);
	while (*fmt)
	{
		if (*fmt && *fmt == '%' && *(fmt + 1) && *(fmt + 1) == 't' && *(fmt + 2) && *(fmt + 2) == 's')
		{
			string_append(s, va_arg(arg, t_string *));
			fmt += 3;
		}
		else if (*fmt && *fmt == '%' && *(fmt + 1) && *(fmt + 1) == 's')
		{
			string_append_cstr(s, va_arg(arg, char *));
			fmt += 2;
		}
		else if (*fmt && *fmt == '%' && *(fmt + 1) && *(fmt + 1) == 'd')
		{
			tmp = ft_itoa(va_arg(arg, int), s->alloc_lvl);
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

void	string_prepend_cstr(t_string *s, const char *cstr)
{
	size_t	i;

	i = 0;
	while (*cstr)
	{
		if (s->len + 2 >= s->capacity)
			add_capacity(s);
		ft_memmove(&s->data[i + 1], &s->data[i], s->len++);
		s->data[i++] = *cstr;
		cstr++;
	}
}

t_string	*string_substr(t_string *s, size_t start, size_t len, int alloc_lvl)
{
	char		*subbed;
	char		*cstr;
	t_string	*new;

	cstr = string_cstr(s, SAFE);
	subbed = ft_substr(cstr, start, len, alloc_lvl);
	new = string_init(subbed, alloc_lvl);
	wfree(subbed);
	wfree(cstr);
	return (new);
}

int	string_cmp(t_string *s1, t_string *s2)
{
	size_t	i;

	i = 0;
	while (i < s1->len)
	{
		if (s1->data[i] != s2->data[i])
			return (s1->data[i] - s2->data[i]);
		i++;
	}
	return (s1->data[i] - s2->data[i]);
}

char	*string_cstr(t_string *s, int alloc_lvl)
{
	char	*cstr;

	cstr = walloc(s->len + 1, alloc_lvl);
	ft_memcpy(cstr, s->data, s->len);
	cstr[s->len] = '\0';
	wfree(s->cstr);
	s->cstr = cstr;
	return (s->cstr);
}

void	string_free(t_string **s)
{
	wfree((*s)->data);
	wfree((*s)->cstr);
	wfree(*s);
	*s = NULL;
}

#ifdef STRINGTEST

/*=============*/
/*   TESTING   */
/*=============*/

#include <stdio.h>

int main()
{
	t_string	*s = string_init("bonjour", SAFE);
	printf("%s\n", string_cstr(s, SAFE));

	string_appendfmt(s, " va arg %s", "literal");
	printf("%s \n", string_cstr(s, SAFE));

	t_string	*s2 = string_init("type string", SAFE);
	string_appendfmt(s, " va arg %ts", s2);
	printf("%s\n", string_cstr(s, SAFE));

	string_appendfmt(s, " et un int %d", 666);
	printf("%s\n", string_cstr(s, SAFE));
	string_free(&s);
	string_free(&s2);
}

#endif
