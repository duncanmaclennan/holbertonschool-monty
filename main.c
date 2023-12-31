#include <ctype.h>
#include "monty.h"
/**
 * push - pushes something
 * @stack: the stack
 * @line_number: the line number
 * @n_str: the string
 */
void push(stack_t **stack, unsigned int line_number, const char *n_str)
{
	stack_t *new_node;

	if (!is_valid_integer(n_str))
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	int num = atoi(n_str);

	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = num;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack != NULL)
	{
		(*stack)->prev = new_node;
	}

	*stack = new_node;
}
/**
 * pall - pushes something
 * @stack: the stack
 * @line_number: the line number
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;

	(void)line_number;

	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

/**
 * pint - pints something
 * @stack: the stack
 * @line_number: the line number
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}

/**
 * is_valid_integer - checks if valid
 * @str: the string
 * Return: 1 if success
 */
int is_valid_integer(const char *str)
{
	if (str == NULL)
		return (0);

	for (int i = 0; str[i] != '\0'; ++i)
	{
		if (i == 0 && str[i] == '-')
		{
			if (str[i + 1] == '\0')
				return (0);
			continue;
		}

		if (!isdigit(str[i]))
			return (0);
	}
	return (1);
}

/**
 * pop - does the pop
 * @stack: the stack
 * @line_number: the line number
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp = *stack;

	*stack = (*stack)->next;

	if (*stack != NULL)
	{
		(*stack)->prev = NULL;
	}
	free(temp);
}

/**
 * swap - does the swap
 * @stack: the stack
 * @line_number: the line number
 */
void swap(stack_t **stack, unsigned int line_number)
{
	int temp;

	// Check if the stack has less than two elements
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	// Swap the top two elements
	temp = (*stack)->n;
	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = temp;
}

/**
 * add - does the add
 * @stack: the stack
 * @line_number: the line number
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	// Check if the stack has less than two elements
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	// Add the top two elements of the stack
	(*stack)->next->n += (*stack)->n;

	// Store the result in the second top element and remove the top element
	temp = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;

	free(temp);
}

/**
 * nop - does the nop
 * @stack: the stack
 * @line_number: the line number
 */
void nop(stack_t **stack, unsigned int line_number)
{
    (void)stack;
    (void)line_number;
}
/**
 * handle_line - does the monty
 * @line: the line
 * @stack: the stack
 * @line_number: the line number
 */
void handle_line(char *line, stack_t **stack, unsigned int line_number)
{
	char *opcode, *argument;

	opcode = strtok(line, " \t\r\n");
	if (opcode == NULL || opcode[0] == '#')
		return;
	argument = strtok(NULL, " \t\r\n");
	if (strcmp(opcode, "push") == 0)
		push(stack, line_number, argument);
	else if (strcmp(opcode, "pall") == 0)
		pall(stack, line_number);
	else if (strcmp(opcode, "pint") == 0)
		pint(stack, line_number);
	else if (strcmp(opcode, "pop") == 0)
		pop(stack, line_number);
	else if (strcmp(opcode, "swap") == 0)
		swap(stack, line_number);
	else if (strcmp(opcode, "add") == 0)
		add(stack, line_number);
	else if (strcmp(opcode, "nop") == 0)
    	nop(stack, line_number);
	else
	{
		fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
		exit(EXIT_FAILURE);
	}
}

/**
 * main - does the monty
 * @argc: the stack
 * @argv: the stack
 * Return: 0 if success
 */
int main(int argc, char **argv)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	unsigned int line_number = 0;
	stack_t *stack = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while ((read = getline(&line, &len, fp)) != -1)
	{
		handle_line(line, &stack, ++line_number);
	}

	fclose(fp);
	free(line);
	free_stack(&stack);
	return (0);
}
