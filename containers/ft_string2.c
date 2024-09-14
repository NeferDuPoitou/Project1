#include "../libft.h"

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
