/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:19:20 by Gecko             #+#    #+#             */
/*   Updated: 2023/10/29 11:19:25 by Gecko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Modified version of strjoin, to use with the destination
// already allocated on the heap. Handles freeing the old pointer

static char	*ft_strjoin_s1_on_the_heap(char *s1, char *s2)
{
	char	*tab;
	size_t	total_size;

	if (!s1 || !s2)
		return (NULL);
	total_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	tab = walloc((total_size) * sizeof(char), SAFE);
	if (!tab)
	{
		wfree(s1);
		return (NULL);
	}
	tab[0] = '\0';
	ft_strlcat(tab, s1, total_size);
	ft_strlcat(tab, s2, total_size);
	wfree(s1);
	return (tab);
}

static size_t	found_newline(char *s)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s == '\n')
		{
			return (i);
		}
		s++;
		i++;
	}
	return (0);
}

// the extract and clean fuction. Creates and allocates the final line
// with the remain's contents until a newline is encountered (including newline)
// and cuts the remains contents from the newline (not included)

static char	*get_line_and_clean_remains(char **remains)
{
	char	*line;
	char	*clean_remains;
	size_t	newline_pos;
	size_t	remains_len;

	newline_pos = 0;
	remains_len = ft_strlen(*remains);
	while ((*remains)[newline_pos] && (*remains)[newline_pos] != '\n')
		newline_pos++;
	if ((*remains)[newline_pos] == '\n')
		newline_pos++;
	line = ft_substr(*remains, 0, newline_pos, SAFE);
	clean_remains = ft_substr(*remains, newline_pos, remains_len - newline_pos, SAFE);
	wfree(*remains);
	*remains = clean_remains;
	if (!line || !clean_remains || ft_strlen(line) == 0)
	{
		wfree(*remains);
		wfree(line);
		*remains = NULL;
		return (NULL);
	}
	return (line);
}

// the read function. Handles growing the remains array by buffer size jumps,
// until a newline is encountered.

static char	*read_from_fd(int fd, char **remains, char *tmp, ssize_t *read_len)
{
	*read_len = 1;
	while (*read_len >= 0)
	{
		ft_bzero(tmp, BUFFER_SIZE + 1);
		*read_len = read(fd, tmp, BUFFER_SIZE);
		if (*read_len == -1)
		{
			wfree(remains[fd]);
			remains[fd] = NULL;
			return (NULL);
		}
		if (!remains[fd])
		{
			remains[fd] = ft_strdup(tmp, SAFE);
		}
		else
		{
			remains[fd] = ft_strjoin_s1_on_the_heap(remains[fd], tmp);
		}
		if (!remains[fd])
			return (NULL);
		if (remains[fd] && (found_newline(remains[fd]) || *read_len == 0))
			return (remains[fd]);
	}
	return (NULL);
}

// main function. Handles fd and buffer size errors,
// and calls the 2 helper functions
// read_from_fd and get_line_and_clean_remains

char	*get_next_line(int fd)
{
	static char	*remains[1024];
	char		tmp[BUFFER_SIZE + 1];
	ssize_t		read_len;

	read_len = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	remains[fd] = read_from_fd(fd, remains, tmp, &read_len);
	if (!remains[fd])
		return (NULL);
	return (get_line_and_clean_remains(&remains[fd]));
}
