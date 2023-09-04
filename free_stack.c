#include <ctype.h>
#include "monty.h"

/**
 * free_stack - frees memory
 * @stack: the stack
 */
void free_stack(stack_t **stack)
{
	stack_t *current_node;
	stack_t *next_node;

	current_node = *stack;
	while (current_node != NULL)
	{
		next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}
	*stack = NULL;
}
