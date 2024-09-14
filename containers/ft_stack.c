#include "../libft.h"
#include <errno.h>

t_stack	*stack_init(int alloc_lvl)
{
	t_stack	*stack;

	stack = walloc(sizeof(t_stack), alloc_lvl);
	if (!stack)
		return (errno = ENOMEM, NULL);
	stack->top = NULL;
	stack->alloc_level = alloc_lvl;
	return (stack);
}

int	stack_push(t_stack *stack, void *data)
{
	t_stack_node	*new_node;

	if (!stack || !data)
		return (errno = EINVAL, -1);
	new_node = (t_stack_node *)walloc(sizeof(t_stack_node), stack->alloc_level);
	if (!new_node)
		return (errno = ENOMEM, -1);
	new_node->data = data;
	new_node->next = stack->top;
	stack->top = new_node;
	return (0);
}

void	*stack_pop(t_stack *stack)
{
	t_stack_node	*temp;
	void			*data;

	if (!stack)
		return (errno = EINVAL, NULL);
	if (stack->top == NULL)
		return (NULL);
	temp = stack->top;
	data = temp->data;
	stack->top = stack->top->next;
	wfree(temp);
	return (data);
}

void	*stack_peek(t_stack *stack)
{
	if (!stack)
		return (errno = EINVAL, NULL);
	if (stack->top)
		return (stack->top->data);
	return (NULL);
}

void	stack_clear(t_stack **stack, void (*del)(void *c))
{
	t_stack_node	*tmp;

	if (!*stack || !del)
	{
		errno = EINVAL;
		return ;
	}
	while ((*stack)->top)
	{
		tmp = (*stack)->top->next;
		del((*stack)->top->data);
		wfree((*stack)->top);
		(*stack)->top = tmp;
	}
	wfree(*stack);
	*stack = NULL;
}
