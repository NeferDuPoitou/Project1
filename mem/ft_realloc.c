#include "../libft.h"
#include <errno.h>
#include <stdio.h>

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size, int alloc_lvl)
{
	void	*newptr;

	if (!ptr)
		return (walloc(new_size, alloc_lvl));
	if (!new_size && ptr)
		return (wfree(ptr), NULL);
	newptr = walloc(new_size, alloc_lvl);
	if (!newptr)
		return (errno = ENOMEM, NULL);
	ft_memcpy(newptr, ptr, old_size);
	wfree(ptr);
	return (newptr);
}
