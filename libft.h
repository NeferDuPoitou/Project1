/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 13:54:12 by Gecko             #+#    #+#             */
/*   Updated: 2023/08/06 17:54:09 by Gecko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

# define SUCCESS 1
# define FAILURE 0
# define ALLOC 10
# define FREE 11
# define CLEAR 12
# define PRINT_SIZE 13
# define CRITICAL 1
# define SAFE 0


/*=============*/
/*    STRING   */
/*=============*/

int		ft_tabtablen(char **tab);
int		ft_strsuffix(char *s, char *pattern);
int		ft_strprefix(char *s, char *pattern);
char	*ft_strtolower(char *s);
void	ft_sorttabtab(char ***array, int rows, int cols);
int		ft_tabtabheigth(char **tab);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strncat(char *dest, const char *src, size_t n);
int		is_blank(char c);
int		has_blank(char *s);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_atoi(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1, int is_critical);
char	*ft_saferdup(const char *s, int is_critical);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strcpy(char *dst, char *src);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_itoa(int n, int is_critical);
char	*ft_strjoin(char const *s1, char const *s2, int is_critical);
char	**ft_split(char const *s, char c, int is_critical);
char	**ft_split_charset(char const *s, char *set, int is_critical);
char	*ft_substr(char const *s, unsigned int start, \
							size_t len, int is_critical);
char	*ft_strtrim(char const *s1, char const *s2, int is_critical);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char), \
										int is_critical);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
int		ft_strcmp(char *s1, char *s2);

/*=============*/
/*     MEM     */
/*=============*/

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size, int is_critical);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size, int alloc_lvl);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);

/*=============*/
/*      IO     */
/*=============*/

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/*=============*/
/*     MATH    */
/*=============*/

int		ft_abs(int x);

/*=============*/
/*  ALLOCATOR  */
/*=============*/

typedef struct s_mlist
{
	void			*c;
	int				critical;
	struct s_mlist	*next;
}	t_mlist;

void	*allocator(int size, int type, void *ptr, int is_critical);
void	*walloc(int size, int is_critical);
void	wfree(void *ptr);
void	wclear(int free_critical);
void	print_allocated_memory_size(t_mlist	*allocs);

t_mlist	*mlistnew(void *content, int is_critical);
void	mlistadd_front(t_mlist **lst, t_mlist *n);
t_mlist	*mlistlast(t_mlist *lst);
void	mlistadd_back(t_mlist **lst, t_mlist *n);
void	free_mlistnode(t_mlist *to_del);
int		mlist_delone(t_mlist **head, t_mlist *to_del);
void	mlist_clear(t_mlist **allocs, int free_critical);

/*=============*/
/*     GNL     */
/*=============*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 666
# endif

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>

char	*get_next_line(int fd);

/*=============*/
/* CONTAINTERS */
/*=============*/

/* LIST */

typedef struct s_lnode
{
	void			*content;
	struct s_lnode	*next;
	struct s_lnode	*prev;
	int				alloc_level;
}	t_lnode;

typedef void (*t_delf)(void *);
typedef void *(*t_dupf)(t_lnode *);

typedef	struct s_lst
{
	t_lnode	*head;
	t_lnode	*tail;
	size_t	size;
	int		alloc_level;
	t_delf	delf;
	t_dupf	dupf;
}	t_lst;

// allocates, initializes and return a new lst struct.
// returns NULL and sets errno to ENOMEM if an allocation fails.
t_lst	*newlst(int is_critical, t_delf, t_dupf);

// allocates, initializes with content and return a new lst node.
// returns NULL and sets errno to EINVAL if content is NULL.
// returns NULL and sets errno to ENOMEM if an allocation fail.
t_lnode	*lstnew(void *content, int is_critical);

// adds the node new to the front of the list l.
// new becomes the new head and if l is empty, the new tail too.
// returns early and sets errno to EINVAL if new or l are NULL.
void	lstadd_front(t_lst *l, t_lnode *new);

// adds the node new to the back of the list l.
// new becomes the new tail and if l is empty, the new head too.
// returns early and sets errno to EINVAL if new of l are NULL.
void	lstadd_back(t_lst *l, t_lnode *new);

// appends a node new after the node t.
// to keep the function O(1), it does not check if t is part of l.
// use with that in mind.
// returns early and sets errno to EINVAL if new, t or l are NULL.
void	lstadd_after(t_lst *l, t_lnode *t, t_lnode *new);

// appends a node new before the node t.
// to keep the function O(1), it does not check if t is part of l.
// use with that in mind.
// returns early and sets errno to EINVAL if new, t or l are NULL.
void	lstadd_before(t_lst *l, t_lnode *t, t_lnode *new);

// replace the node t with new.
// to keep the function O(1), it does not check if t is part of l.
// use with that in mind.
// does nothing in empty lists.
// uses delf to deallocate memory inside content.
// returns early and sets errno to EINVAL if l, t or new are NULL,
// or if l is an empty list.
void	lst_replace(t_lst *l, t_lnode *t, t_lnode *new);

// merges the list new in front of the list l.
// does nothing if new is empty.
// returns early and sets errno to EINVAL if l or new are NULL,
// or if new is an empty list.
void	lstmerge_front(t_lst *l, t_lst *new);

// merges the list new at the back of the list l.
// does nothing if new is empty.
// returns early and sets errno to EINVAL if l or new are NULL,
// or if new is an empty list.
void	lstmerge_back(t_lst *l, t_lst *new);

// merge the list new after the node t in the list l.
// to keep the function O(1), it does not check if t is in l.
// returns early and sets errno to EINVAL if l, t or new are NULL,
// or if new is an empty list.
void	lstmerge_after(t_lst *l, t_lnode *t, t_lst *new);

// merges the list new after the node t in the list l.
// to keep the function O(1), it does not check if t is in l.
// returns early and sets errno to EINVAL if l, t or new are NULL,
// or if new is an empty list.
void	lstmerge_before(t_lst *l, t_lnode *t, t_lst *new);

// returns the fist occurence of to_find in the list l
// returns NULL if no occurence is found
// returns NULL and sets errno to EINVAL if l or to_find are null.
t_lnode	*lst_find(t_lst *l, void *to_find);

// allocates and returns a copy of node
// dupf is function pointer used to create the copy of content.
// also duplicates the allocation level of the node.
// does not duplicates the links.
// returns NULL and sets errno to einval if node of dupf are NULL.
// returns NULL and sets errno to ENOMEM if an allocation fails.
t_lnode	*lst_dupnode(t_lnode *node, void *(*dupf)(t_lnode *));

// Allocates and returns a new list containing n nodes starting at node t in list l.
// Uses the function dupf to perform the copy of content.
// Copies the allocation level of l.
// if n is 0 or greater than the size of l, the list is dupped until the end.
// Returns NULL and sets errno to EINVAL if l or t is NULL, or if n is 0.
// Returns NULL and sets errno to ENOMEM if an allocation fails.
t_lst	*lst_dupn(t_lst *l, t_lnode *t, int n);

// allocated and returns a copy of l
// Returns NULL and sets errno to EINVAL if l or dupf are NULL.
// Returns NULL and sets errno to ENOMEM if an allocation fails.
t_lst	*lst_dup(t_lst *l);

// deletes the node d from the list l, updating the links and the size.
// returns early and sets errno to EINVAL if l or d are NULL or if l is
// an empty list.
void	lst_delone(t_lst *l, t_lnode *d);

// iterates of the list l, and removes every node where
// cond returns a non 0 number.
void	lst_remove_if(t_lst *l, int (*cond)(t_lnode *));

// iterates of the list l and applies f if cond returns a non 0 value.
// returns early and sets errno to EINVAL if l, cond or f are NULL,
// or if l is an empty list
void	lst_do_if(t_lst *l, int (*cond)(t_lnode *), void (*f)(t_lnode *));

// iterates over the list l and applies f while cond returns a non 0 value, or until
// the end of l.
// returns early and sets errno to EINVAL if l, cond or f are NULL,
// or if l is an empty list
void	lst_do_while(t_lst *l, int (*cond)(t_lnode *), void (*f)(t_lnode *));

// deletes every nodes and every node's contents in list l,
// sets l'head and tail to NULL and size to 0.
// does not free l.
// uses del to deallocate memory inside content.
// returns early and sets errno to EINVAL if l is NULL.
void	lstclear(t_lst *l);

// applies the function f to each element of l in order.
// returns early and sets errno to EINVAL if l or f are NULL,
// or if l is an empty list.
void	lstiter(t_lst *l, void (*f)(t_lnode *));

// applies the function f to each element of l in reverse.
// returns early and sets errno to EINVAL if l or f are NULL,
// or if l is an empty list.
void	lstiter_reverse(t_lst *l, void (*f)(t_lnode *));

// allocates and returns a copy of l, with the function f applied on it.
// dupf is used to handle the copy of l's content.
// returns NULL and sets errno to EINVAL if l, f or dupf are NULL, of if
// l is an empty list.
// returns NULL and sets errno to ENOMEM if an allocation fails.
t_lst	*lstmap(t_lst *l, void (*f)(t_lnode *));

// reverses the list l.
// returs early and sets errno to EINVAL if l or f are NULL,
// or if l is an empty list.
void	lst_reverse(t_lst *l);

// allocates and returns a new lst starting at t.
// the original lst ends one before t.
// t cannot be l's head or tail.
// performs a deep copy of of the nodes and contents using dupf,
// allocating new memory while freeing the old memory with del.
// returns NULL and sets errno to EINVAL if l, or t are NULL,
// if l is empty or if t is l's head or tail.
// returns NULL and sets errno to ENOMEM if an allocation fails.
t_lst	*lst_split_at_deep(t_lst *l, t_lnode *t);

// allocates and returns a new lst starting at t.
// the original lst ends one before t.
// t cannot be l's head or tail.
// performs a shallow copy of the nodes and contents,
// so that the pointers will be the same as the ones in the ol l.
// returns NULL and sets errno to EINVAL if l, or t are NULL,
// if l is empty or if t is l's head or tail.
// returns NULL and sets errno to ENOMEM if an allocation fails.
// complexity: O(n) because we need to calculate the size of the new
// lst.
t_lst	*lst_split_at_shallow(t_lst *l, t_lnode *t);

// returns the last element of a lst by iterating over each of its elements.
// dont use it unless you really need it, prefer reaching for l->tail.
t_lnode	*lstlast(t_lst *l);

// returns the size of a lst by iterating over each of its elements.
// dont use it unless you really need it, prefer reaching for l->size.
size_t	lstsize(t_lst *l);


/* STACK */


typedef struct s_stack_node
{
	void				*data;
	struct s_stack_node	*next;
}						t_stack_node;

typedef struct s_stack
{
	t_stack_node		*top;
	int					alloc_level;
}						t_stack;

// allocates, intializes and returns a new stack struct.
// returns NULL and sets errno to ENOMEM if an allocation fails.
t_stack	*stack_init(int alloc_lvl);

// allocates and push a new node in the stack.
// returns -1 and sets errno to EINVAL if stack or data are NULL.
// returns -1 and sets errno to ENOMEM if an allocation fails.
// returns 0 on success.
int		stack_push(t_stack *stack, void *data);

// removes and returns the top node from the stack.
// returns NULL if stack->top if NULL.
// returns NULL and sets errno to EINVAL if stack is NULL.
void	*stack_pop(t_stack *stack);

// returns the top node from the stack.
// returns NULL if stack->top if NULL.
// returns NULL and sets errno to EINVAL if stack is NULL.
void	*stack_peek(t_stack *stack);

// deallocate the whole stack, using del to dealocate user data.
// frees stack and sets it to NULL.
void	stack_clear(t_stack **stack, void (*del)(void *c));


/*   VECTOR    */


typedef void (*delfun)(void *);
typedef	void *(*dupfun)(void *);

typedef struct s_vector
{
	void	**data;
	size_t	size;
	size_t	capacity;
	int		alloc_lvl;
	delfun	delfun;
	dupfun	dupfun;
}	t_vector;

//
t_vector	*vector_init(size_t initial_capacity, \
					  int alloc_lvl, \
					  void (*delfun)(void *), \
					  void *(*dupfun)(void *));
//
void	vector_resize(t_vector *v, size_t new_capacity);
//
void	vector_add(t_vector *v, void *elem);
//
void	*vector_get(t_vector *v, size_t index);
//
void	vector_remove(t_vector *v, size_t index);
//
void	*vector_pop(t_vector *v);
//
void	vector_clear(t_vector *v);
//
int		vector_isempty(t_vector *v);
//
int		vector_reserve(t_vector *v, size_t new_capacity);
//
void	vector_shrink_to_fit(t_vector *v);
//
size_t	vector_find(t_vector *v, void *elem);
//
void	vector_sort(t_vector *v, int (*cmp)(const void *, const void *));
//
void	vector_reverse(t_vector *v);
//
t_vector	*vector_dup(t_vector *v, int alloc_lvl);
//
void	vector_iter(t_vector *v, void (*f)(void *));;
//
t_vector	*vector_map(t_vector *v, void (*f)(void *), int alloc_lvl);
//
t_vector	*vector_filter(t_vector *v, int (*cond)(void *), int alloc_lvl);
//
t_vector	*vector_merge(t_vector *v1, t_vector *v2, int alloc_lvl);
//
t_vector	*vector_split(t_vector *v, size_t index, int alloc_lvl);
//
void	vector_swap(t_vector *v, size_t index1, size_t index2);
//
void	*vector_find_if(t_vector *v, int (*pred)(void *));
//
int	vector_contains(t_vector *v, void *elem);
//
void	vector_push_front(t_vector *v, void *elem);
//
void	*vector_pop_front(t_vector *v);
//
t_vector	*vector_slice(t_vector *v, size_t start, size_t end, int alloc_lvl);
//
void	vector_copy_to_array(t_vector *v, void **array);
//
size_t	vector_capacity(t_vector *v);
//
void	vector_foreach(t_vector *v, void (*f)(void *, size_t));;
//
void	vector_set(t_vector *v, size_t index, void *elem);
//
void	vector_sort_range(t_vector *v, size_t start, size_t end, int (*cmp)(const void *, const void *));;
//
void	vector_iter(t_vector *v, void (*f)(void *));
//
void	vector_free(t_vector **v);

#endif  // LIBFT_H


















